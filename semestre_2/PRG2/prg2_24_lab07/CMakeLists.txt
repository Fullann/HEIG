cmake_minimum_required(VERSION 3.26)
project(prg2_24_lab07 C)

set(CMAKE_C_STANDARD 11)

include_directories(student)

add_executable(prg2_24_lab07
        student/bmp.c
        student/bmp.h
        student/compare.c
        student/gray.c
        student/pepper.c)
