cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(QtPlayground)

find_package(Qt6 COMPONENTS Widgets Core Gui Sql REQUIRED)

add_executable(QtPlayground main.cpp)

target_link_libraries(QtPlayground PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt6::Sql)


#  sudo apt install libqt6multimedia6 qt6-multimedia-dev