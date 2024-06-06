cmake_minimum_required(VERSION 3.01)
project(Hasher)
set(CMAKE_CXX_STANDARD 20)

add_executable(Chainage main_chainage.cpp HashMapChainage.h)
add_executable(Sondage main_sondage.cpp HashMapSondage.h)