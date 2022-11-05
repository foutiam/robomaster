cmake_minimum_required(VERSION 3.15)
project(hw3)

find_package(OpenCV 4 REQUIRED)
find_package(Eigen3 3.4 NO_MODULE)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/usr/include/eigen3")
# include_directories(${eigen3_INCLUDE_DIRS})



add_executable(1 src/1.cpp)
target_link_libraries(1 ${OpenCV_LIBS})
target_link_libraries(1 Eigen3::Eigen)

add_executable(2 src/2.cpp)
target_link_libraries(2 ${OpenCV_LIBS})
target_link_libraries(2 Eigen3::Eigen)

# add_executable(3 src/3.cpp)
# target_link_libraries(3 ${OpenCV_LIBS})    
# target_link_libraries(3 Eigen3::Eigen)
