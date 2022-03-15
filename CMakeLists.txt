cmake_minimum_required(VERSION 3.21)
project(5c C)

set(CMAKE_C_STANDARD 11)

add_executable(5c main.c sortFunctions/sortFunctions.c algorithm/algorithm.c)

add_subdirectory(sortFunctions)
add_subdirectory(algorithm)