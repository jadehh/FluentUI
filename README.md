# FluentUI
FluentUI

## 安装
```bash

"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars32.bat"
mkdir build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=D:\SDKS\Qt\5.15.2\msvc2019 -DCMAKE_INSTALL_PREFIX="D:\SDKS\FluentUI" ..
cmake --build .  --config Release --target install

cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=D:\SDKS\Qt\5.15.2\msvc2019 -DCMAKE_INSTALL_PREFIX="D:\SDKS\FluentUI" ..
cmake --build .  --config Debug --target install

```
> 编译完成之后需要删除build文件夹不能有其他Cmake的文件