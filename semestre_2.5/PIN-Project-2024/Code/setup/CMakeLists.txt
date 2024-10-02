cmake_minimum_required(VERSION 3.16)
project(pin-2024)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

# Add the executable
add_executable(${PROJECT_NAME}
        main.cpp
        Particle.cpp
        Robot.cpp
        State.cpp
        Algo_traj.cpp
)

