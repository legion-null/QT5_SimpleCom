# 指定CMake最低版本号
cmake_minimum_required(VERSION 3.0)

# 将项目文件名称作为项目名称
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# 指定项目名称和语言
project(${PROJECT_NAME} LANGUAGES CXX)

# 包含头文件
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 自动运行MOC
set(CMAKE_AUTOMOC ON)

# 自动将UI文件转换为源代码
set(CMAKE_AUTOUIC ON)

# Qt5相关库文件
find_package(Qt5 COMPONENTS Core Gui Widgets SerialPort WebKitWidgets REQUIRED)

# 添加源代码文件
set(SRC_FILES
	src/main.cpp
	src/simplecom.cpp
)

# 构建可执行程序
add_executable(${PROJECT_NAME} ${SRC_FILES})

# 链接相关库文件
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::SerialPort Qt5::WebKitWidgets)
