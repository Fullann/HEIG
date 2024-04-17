cmake_minimum_required(VERSION 3.16)
project(ASD-2024-L3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(
        L3-demo
        #main_somebits_demo.cpp
        #main_check-tris.cpp
        main_time.cpp
        tri_rapide.h
        tri_par_base.h)
