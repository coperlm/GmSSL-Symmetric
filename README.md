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
