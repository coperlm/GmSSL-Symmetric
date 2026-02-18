# GmSSL-SYMMETRIC

## 改动与声明

fork自`GmSSL3`，修复并整理对称加密。此次fork的原版本执行过程中存在报错，主要集中在`TLS13`部分，此版本已经把相关调用与优化删除，并聚焦于代码的具体实现部分。具体包括： `SM4` `SM3` `AES` 三个算法，旨在学习和辅助构建`SM-FAEST`。


## 编译与安装

采用cmake构建系统，clone并进入源码目录，执行：

```bash
mkdir build
cd build
cmake ..
make
ctest
cd ..
```

## 运行结果

```
Test project /home/coper/Desktop/GmSSL-Symmetric/build
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
