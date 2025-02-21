cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(/Zc:__cplusplus)

project(QtPlayground)

include_directories("C:\\Qt\\6.8.2\\msvc2022_64\\include\\QtWidgets"
                    "C:\\Qt\\6.8.2\\msvc2022_64\\include\\QtCore"
                    "C:\\Qt\\6.8.2\\msvc2022_64\\include")

link_directories("C:\\Qt\\6.8.2\\msvc2022_64\\lib")

set(Qt6Widgets_DIR "C:\\Qt\\6.8.2\\msvc2022_64\\lib\\cmake\\Qt6Widgets")
find_package(Qt6Widgets REQUIRED)
set(Qt6Core_DIR "C:\\Qt\\6.8.2\\msvc2022_64\\lib\\cmake\\Qt6Core")
find_package(Qt6Core REQUIRED)

add_executable(QtPlayground main.cpp)

target_link_libraries(QtPlayground PRIVATE Qt6Widgets Qt6Core)