cmake_minimum_required(VERSION 3.10)
project(GmSSL C)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(include)
include(CheckSymbolExists)

add_compile_options(-O3)

option(ENABLE_TEST_SPEED "Enable test speed" OFF)
option(ENABLE_SMALL_FOOTPRINT "Enable small code size" OFF)

add_definitions(-DENABLE_SM4_ECB)
add_definitions(-DENABLE_SM4_OFB)
add_definitions(-DENABLE_SM4_CFB)
add_definitions(-DENABLE_SM4_CCM)
add_definitions(-DENABLE_SM4_XTS)
add_definitions(-DENABLE_SM4_CBC_MAC)
add_definitions(-DENABLE_AES)

set(src
	src/version.c
	src/debug.c
	src/sm4.c
	src/sm4_ecb.c
	src/sm4_cbc.c
	src/sm4_ctr.c
	src/sm4_cfb.c
	src/sm4_ofb.c
	src/sm4_ccm.c
	src/sm4_gcm.c
	src/sm4_xts.c
	src/sm4_cbc_mac.c
	src/sm3.c
	src/sm3_hmac.c
	src/sm3_kdf.c
	src/sm3_pbkdf2.c
	src/sm3_digest.c
	src/aes.c
	src/aes_modes.c
	src/gf128.c
	src/ghash.c
	src/hex.c
	src/rand_unix.c
)

set(tests
	sm4
	sm4_ecb
	sm4_cbc
	sm4_ctr
	sm4_cfb
	sm4_ofb
	sm4_ccm
	sm4_gcm
	sm4_xts
	sm4_cbc_mac
	sm3
	aes
)

if (ENABLE_SMALL_FOOTPRINT)
	message(STATUS "ENABLE_SMALL_FOOTPRINT is ON")
	add_definitions(-DENABLE_SMALL_FOOTPRINT)
endif()

if (ENABLE_TEST_SPEED)
	message(STATUS "ENABLE_TEST_SPEED is ON")
	add_definitions(-DENABLE_TEST_SPEED)
endif()

check_symbol_exists(getentropy "unistd.h" HAVE_GETENTROPY)
if (HAVE_GETENTROPY)
	message(STATUS "have getentropy")
else()
	message(FATAL_ERROR "getentropy not found, Linux random source is required")
endif()

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(gmssl ${src})

SET_TARGET_PROPERTIES(gmssl PROPERTIES VERSION 3.1 SOVERSION 3)

install(TARGETS gmssl ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/gmssl DESTINATION include)

enable_testing()

foreach(test_name ${tests})
	add_executable(test_${test_name} tests/${test_name}test.c)
	target_link_libraries(test_${test_name} gmssl)
	add_test(NAME test_${test_name} COMMAND test_${test_name})
endforeach()
