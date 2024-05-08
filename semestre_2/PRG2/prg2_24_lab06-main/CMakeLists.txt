cmake_minimum_required(VERSION 3.27)
project(prg2_24_lab06 C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(prg2_24_lab06
        src/cargo_ship.c
        src/cargo_ship.h
        src/combat_ship.c
        src/combat_ship.h
        src/command_ship.c
        src/command_ship.h
        src/config.h
        src/main.c
        src/ship.c
        src/ship.h)
