# CMake environment for SLAM BackEnd
> Ceres-solver, Eigen3.3 built in

# Cmake folder hierarchy
## Top-level CMakeLists
```
cmake_minimum_required(VERSION 3.22)
project(SLAM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(module)
add_compile_definitions(PROJECT_DIR="${CMAKE_SOURCE_DIR}")

# add_executable(basicEX examples/1_helloworld.cpp)
# target_link_libraries(basicEX PRIVATE module)

# add_executable(numericDiff examples/2_helloworld_numeric_diff.cpp)
# target_link_libraries(numericDiff PRIVATE module)

# add_executable(analyticDiff examples/3_helloworld_analytic_diff.cpp)
# target_link_libraries(analyticDiff PRIVATE module)

# add_executable(powell examples/4_powell.cpp)
# target_link_libraries(powell PRIVATE module)

# add_executable(CF examples/5_curve_fitting.cpp)
# target_link_libraries(CF PRIVATE module)

# add_executable(robustCF examples/6_robust_curve_fitting.cpp)
# target_link_libraries(robustCF PRIVATE module)

# add_executable(simpleBA examples/7_simple_BA.cpp)
# target_link_libraries(simpleBA PRIVATE module)

# add_executable(RosenBrock examples/8_rosenbrock.cpp)
# target_link_libraries(RosenBrock PRIVATE module)

# add_executable(Beale examples/9_beale.cpp)
# target_link_libraries(Beale PRIVATE module)

add_executable(BA examples/10_BA.cpp)
target_link_libraries(BA PRIVATE module bal_problem)
```
## Module CMakeLists
```
cmake_minimum_required(VERSION 3.22)
project(module LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MODULE_SOURCE_FILES1 src/module.cpp)
set(MODULE_SOURCE_FILES2 src/bal_problem.cpp)

add_library(module ${MODULE_SOURCE_FILES1})
add_library(bal_problem ${MODULE_SOURCE_FILES2})
 
# find_package(OpenCV REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/OpenCV/install/lib/cmake/opencv4)
find_package(Eigen3 REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/eigen/install/share/eigen3/cmake)
find_package(Ceres REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/ceres/install/lib/cmake/Ceres)
# find_package(Pangolin REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/Pangolin/install/lib/cmake/Pangolin)

set(Eigen3_LIBS Eigen3::Eigen)
set(CERES_LIBS ${CERES_LIBRARIES})
# set(PANGOLIN_LIBS ${Pangolin_LIBRARIES})

set(Eigen3_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/thirdparty/eigen/install/include)
set(CERES_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/thirdparty/g2o/install/include)

# Path validation
message("Eigen3_LIBS            - ${Eigen3_LIBS}")
message("Eigen3_INCLUDE_DIRS    - ${Eigen3_INCLUDE_DIRS}")
message("CERES_LIBS             - ${CERES_LIBRARIES}")
message("CERES_INCLUDE_DIRS     - ${CERES_INCLUDE_DIRS}")


target_include_directories(module PUBLIC
                            include
                            # ${OpenCV_INCLUDE_DIRS}
                            ${Eigen3_INCLUDE_DIRS}
                            ${CERES_INCLUDE_DIRS}
                            # ${Pangolin_INCLUDE_DIRS}
                            )

target_link_libraries(module PUBLIC
                        # ${OpenCV_LIBS}
                        ${Eigen3_LIBS}
                        ${CERES_LIBS}
                        # ${PANGOLIN_LIBS}
                        )

target_include_directories(bal_problem PUBLIC
                        include
                        # ${OpenCV_INCLUDE_DIRS}
                        ${Eigen3_INCLUDE_DIRS}
                        ${CERES_INCLUDE_DIRS}
                        # ${Pangolin_INCLUDE_DIRS}
                        )

target_link_libraries(bal_problem PUBLIC
                    # ${OpenCV_LIBS}
                    ${Eigen3_LIBS}
                    ${CERES_LIBS}
                    # ${PANGOLIN_LIBS}
                    )
```
