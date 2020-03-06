cmake_minimum_required(VERSION 3.1.6)
project(bst_visualization)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH ${CMAKE_Qt5_PATH})

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(include/bst_visualization)

add_executable(balanced src/redblack.cpp src/bstnode.cpp src/balancedbstnode.cpp src/generaterandominteger.cpp)
add_executable(not_balanced src/main.cpp src/generaterandominteger.cpp src/bstnode.cpp)

target_link_libraries(not_balanced Qt5::Widgets)
target_link_libraries(balanced Qt5::Widgets)