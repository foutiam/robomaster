cmake_minimum_required(VERSION 3.15)
project(hw5)

set(CMAKE_BUILD_TYPE "Release")
add_definitions("-DENABLE_SSE")

find_package(OpenCV 4 REQUIRED)
find_package(Eigen3 3.4 NO_MODULE)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("/usr/include/eigen3")
# include_directories(${eigen3_INCLUDE_DIRS})

#设置使用C++11编译
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_executable(1 src/1.cpp)
target_link_libraries(1 ${OpenCV_LIBS})
target_link_libraries(1 Eigen3::Eigen)

add_library(VO src/VO.cpp)
target_link_libraries(VO ${OpenCV_LIBS})


add_executable(2 src/2.cpp src/VO.cpp)
target_link_libraries(2 ${OpenCV_LIBS})

# add_executable(3 src/3.cpp)
# target_link_libraries(3 ${OpenCV_LIBS})    
# target_link_libraries(3 Eigen3::Eigen)

# add_executable(4 src/4.cpp)
# target_link_libraries(4 ${OpenCV_LIBS})    
# target_link_libraries(4 Eigen3::Eigen)