cmake_minimum_required(VERSION 3.22)
project(module LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MODULE_SOURCE_FILES src/module.cpp)

add_library(module ${MODULE_SOURCE_FILES})
 
find_package(OpenCV REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/OpenCV/install/lib/cmake/opencv4)
find_package(Eigen3 REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/Eigen3/install/share/eigen3/cmake)
find_package(Pangolin REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/Pangolin/install/lib/cmake/Pangolin)

set(Eigen3_LIBS Eigen3::Eigen)
set(PANGOLIN_LIBS ${Pangolin_LIBRARIES})

target_include_directories(module PUBLIC
                            include
                            ${OpenCV_INCLUDE_DIRS}
                            ${Eigen3_INCLUDE_DIRS}
                            ${Pangolin_INCLUDE_DIRS}
                            )

target_link_libraries(module PUBLIC
                        ${OpenCV_LIBS}
                        ${Eigen3_LIBS}
                        ${PANGOLIN_LIBS})