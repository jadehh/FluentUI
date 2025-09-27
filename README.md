# FluentUI
FluentUI

## Windows 编译 32 位 Debug

```bash
"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
mkdir build_debug && cd build_debug 
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=D:\SDKS\Qt\5.15.2\msvc2019  -D JADE_TOOLS_DIR="D:\SDKS\jade_tools-x86" -DCMAKE_INSTALL_PREFIX="D:\SDKS\FluentUI" ..
cmake --build .  --config Debug --target install
```

## Windows 编译 32 位 Release
```bash

"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat"
mkdir build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=D:\SDKS\Qt\5.15.2\msvc2019 -D JADE_TOOLS_DIR="D:\SDKS\jade_tools-x86" -DCMAKE_INSTALL_PREFIX="D:\SDKS\FluentUI" ..
cmake --build .  --config Release --target install

```
> 编译完成之后需要删除build文件夹不能有其他Cmake的文件