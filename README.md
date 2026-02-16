# GmSSL-SYMMETRIC

fork自GmSSL3，专注对称加密

## 编译与安装

GmSSL 3 采用了cmake构建系统。下载源代码后将其解压缩，进入源码目录，执行：

```bash
rm -rf ./build
mkdir build
cd build
cmake ..
make
ctest
cd ..
```

## Result

```
Test project /home/coper/桌面/GmSSL-Symmetric/build
      Start  1: test_sm4
 1/12 Test  #1: test_sm4 .........................   Passed    0.23 sec
      Start  2: test_sm4_ecb
 2/12 Test  #2: test_sm4_ecb .....................   Passed    0.00 sec
      Start  3: test_sm4_cbc
 3/12 Test  #3: test_sm4_cbc .....................   Passed    0.00 sec
      Start  4: test_sm4_ctr
 4/12 Test  #4: test_sm4_ctr .....................   Passed    0.00 sec
      Start  5: test_sm4_cfb
 5/12 Test  #5: test_sm4_cfb .....................   Passed    0.00 sec
      Start  6: test_sm4_ofb
 6/12 Test  #6: test_sm4_ofb .....................   Passed    0.00 sec
      Start  7: test_sm4_ccm
 7/12 Test  #7: test_sm4_ccm .....................   Passed    0.00 sec
      Start  8: test_sm4_gcm
 8/12 Test  #8: test_sm4_gcm .....................   Passed    0.00 sec
      Start  9: test_sm4_xts
 9/12 Test  #9: test_sm4_xts .....................   Passed    0.00 sec
      Start 10: test_sm4_cbc_mac
10/12 Test #10: test_sm4_cbc_mac .................   Passed    0.00 sec
      Start 11: test_sm3
11/12 Test #11: test_sm3 .........................   Passed    0.00 sec
      Start 12: test_aes
12/12 Test #12: test_aes .........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 12

Total Test time (real) =   0.26 sec
```
