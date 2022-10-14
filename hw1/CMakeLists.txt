cmake_minimum_required(VERSION 3.15)
project(hw1)

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(2 src/2.cpp)
target_link_libraries(2 ${OpenCV_LIBS})

add_executable(3 src/3.cpp)
target_link_libraries(3 ${OpenCV_LIBS})    