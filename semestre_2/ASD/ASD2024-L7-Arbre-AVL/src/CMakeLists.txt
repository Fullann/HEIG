cmake_minimum_required(VERSION 3.15)
project(ASD2024_L7_AVL_Tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(AVL-Tree main.cpp)
add_subdirectory(catch2_tests)