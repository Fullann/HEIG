cmake_minimum_required(VERSION 3.16)
project(ASD2022-L1-Complexite)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(L1-example example.cpp
        OpCounter.cpp
        OpCounter.h
        #1.main.cpp
        #2.main.cpp
        3.main.cpp
        tris.cpp)