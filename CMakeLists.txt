cmake_minimum_required(VERSION 3.22)
project(SLAM LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(module)
add_compile_definitions(PROJECT_DIR="${CMAKE_SOURCE_DIR}")

add_executable(main examples/W15D3.cpp)

target_link_libraries(main PRIVATE
                        module)

