cmake_minimum_required(VERSION 3.27)
project(prg2_24_lab08 C)

set(CMAKE_C_STANDARD 11)

include_directories(student)

add_executable(prg2_24_lab08
        student/btree.c
        student/btree.h
        student/unit_test.c)
