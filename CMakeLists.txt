cmake_minimum_required(VERSION 3.22)
project(natpmp C)

set(CMAKE_C_STANDARD 99)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
