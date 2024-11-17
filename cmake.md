[TOC]

<br>

> Refer：[RUUOOB.COM](https://www.runoob.com/cmake/cmake-basic.html)

# Cmake 基础



## 文件结构和基本语法

1. 指定 CMake 的最低版本要求：
```Cmake
cmake_minimum_required(VERSION <version>)
```
2. 定义项目的名称和使用的编程语言：
```Cmake
project(<project_name> [<language>...])
```
3. 指定要生成的可执行文件和其源文件：
```Cmake
add_executable(<target> <source_files>...)
```
4. 创建一个库（静态库或动态库）及其源文件：
```Cmake
add_library(<target> <source_files>...)
```
5. 链接目标文件与其他库：
```Cmake
target_link_libraries(<target> <libraries>...)
```
6. 添加头文件搜索路径：
```Cmake
include_directories(<dirs>...)
```
7. 设置变量的值：
```Cmake
set(<variable> <value>...)
# 例如
set(CMAKE_CXX_STANDARD 11)
```
8. 设置目标属性：
```Cmake
target_include_directories(TARGET target_name
                          [BEFORE | AFTER]
                          [SYSTEM] [PUBLIC | PRIVATE | INTERFACE]
                          [items1...])
# 例如：
target_include_directories(MyExecutable PRIVATE ${PROJECT_SOURCE_DIR}/include)
```
9、安装规则：
```Cmake
install(TARGETS target1 [target2 ...]
        [RUNTIME DESTINATION dir]
        [LIBRARY DESTINATION dir]
        [ARCHIVE DESTINATION dir]
        [INCLUDES DESTINATION [dir ...]]
        [PRIVATE_HEADER DESTINATION dir]
        [PUBLIC_HEADER DESTINATION dir])
# 例如：
install(TARGETS MyExecutable RUNTIME DESTINATION bin)
```
10、条件语句 (if, elseif, else, endif 命令)
```Cmake
if(expression)
  # Commands
elseif(expression)
  # Commands
else()
  # Commands
endif()
# 例如：
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message("Debug build")
endif()
```
11、自定义命令 (add_custom_command 命令)：
```Cmake
add_custom_command(
   TARGET target
   PRE_BUILD | PRE_LINK | POST_BUILD
   COMMAND command1 [ARGS] [WORKING_DIRECTORY dir]
   [COMMAND command2 [ARGS]]
   [DEPENDS [depend1 [depend2 ...]]]
   [COMMENT comment]
   [VERBATIM]
)
# 例如：
add_custom_command(
   TARGET MyExecutable POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E echo "Build completed."
)
```


---
## 变量
- 定义变量：
`set(MY_VAR "Hello World")`
- 使用变量：
`message(STATUS "Var MY_VAR is ${MY_VAR}")`

---
## 查找库和包 -- find_package() 指令
> `CMake` 可以通过 `find_package()` 指令自动检测和配置外部库和包。
> 
> 常用于查找系统安装的库或第三方库。

<br>

基本用法：
`find_package(Boost REQUIRED)`

指定版本：
`find_package(Boost 1.70 REQUIRED)`

查找库并指定路径：
`find_package(OpenCV REQUIRED PATHS /path/to/opencv)`

使用查找到的库：
`target_link_libraries(MyExecutable Boost::Boost)`

设置包含目录和链接目录：
`include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})`

> 实例 
> ```Cmake
> cmake_minimum_required(VERSION 3.10)
> project(MyProject CXX)
> 
> # 查找 Boost 库
> find_package(Boost REQUIRED) # 添加源文件
> add_executable(MyExecutable main.cpp)
> 
> # 链接 Boost 库
> target_link_libraries(MyExecutable Boost::Boost)
> ```

-------
# Cmake 构建流程

### 1. 创建构建目录

创建构建目录：在项目的根目录下，创建一个新的构建目录。例如，可以创建一个名为 build 的目录。
- **`mkdir build`**
- **`cd build`**

### 2. 使用 CMake 生成构建文件
- 在构建目录中运行 CMake，以生成适合当前平台的构建系统文件（例如 `Makefile`、`Ninja` 构建文件、`Visual Studio` 工程文件等）。

- 运行 CMake 配置：在构建目录中运行 CMake 命令，指定源代码目录。源代码目录是包含 `CMakeLists.txt` 文件的目录。
  - **`cmake ..`**

- 如果需要指定生成器（如 Ninja、Visual Studio），可以使用 -G 选项。例如：
  - **`cmake -G "Ninja" ..`**


- 如果需要指定构建类型（如 `Debug` 或 `Release`），可以使用 `-DCMAKE_BUILD_TYPE` 选项。例如：
  - **`cmake -DCMAKE_BUILD_TYPE=Release ..`**

### 3. 编译和构建
使用 `Makefile`（或类似构建系统）：如果使用 `Makefile`，可以运行 `make` 命令来编译和构建项目。

- **`make`**
如果要构建特定的目标，可以指定目标名称。例如：

   - **`make MyExecutable`**
使用 `Ninja`：如果使用 `Ninja` 构建系统，运行 `ninja` 命令来编译和构建项目。

- **`ninja`**
与 make 类似，可以构建特定的目标：
  - **`ninja MyExecutable`**
使用 `Visual Studio`：如果生成了 `Visual Studio` 工程文件，可以打开 `.sln` 文件，然后在 `Visual Studio` 中选择构建解决方案。

- 也可以使用 `msbuild` 命令行工具来编译：
`msbuild MyProject.sln /p:Configuration=Release`

### 4. 清理构建文件
构建过程中生成的中间文件和目标文件可以通过清理操作删除。

使用 `Makefile`：运行 `make clean` 命令（如果定义了清理规则）来删除生成的文件。

- `make clean`
使用 Ninja：运行 `ninja clean` 命令（如果定义了清理规则）来删除生成的文件。

- `ninja clean`
手动删除：可以手动删除构建目录中的所有文件，但保留源代码目录不变。例如：

- `rm -rf build/*`

### 5. 重新配置和构建
如果修改了 `CMakeLists.txt` 文件或项目设置，可能需要重新配置和构建项目。

重新运行 CMake 配置：在构建目录中重新运行 CMake 配置命令。
`cmake ..`

重新编译：使用构建命令重新编译项目。
`make`



# Cmake 实例

```Cmake
cmake_minimum_required(VERSION 3.10)   # 指定最低 CMake 版本

project(MyProject VERSION 1.0)          # 定义项目名称和版本

# 设置 C++ 标准为 C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 添加源文件
add_library(MyLib src/mylib.cpp)        # 创建一个库目标 MyLib
add_executable(MyExecutable src/main.cpp)  # 创建一个可执行文件目标 MyExecutable

# 链接库到可执行文件
target_link_libraries(MyExecutable MyLib)
```

Terminal:
`mkdir build`
`cd build`
`cmake ..`
`make`
`./MyExecutable`
`make clean` | `rm -rf build/*`