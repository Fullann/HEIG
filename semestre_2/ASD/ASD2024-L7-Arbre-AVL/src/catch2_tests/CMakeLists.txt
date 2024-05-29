set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS --coverage)
add_executable(AVL-tests avlTest.cpp catch_amalgamated.cpp)