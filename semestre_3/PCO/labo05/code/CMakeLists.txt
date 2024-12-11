cmake_minimum_required(VERSION 3.5)
project(PROG_LAB05 LANGUAGES CXX)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)
include_directories(/usr/local/include)
find_library(PCOSYNCHRO_LIB pcosynchro /usr/local/lib)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/multithreadedsort.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/quicksort.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/utils.h
)

add_executable(PCO_LAB05_tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp ${HEADERS})
add_executable(PCO_LAB05_benchmarks ${CMAKE_CURRENT_SOURCE_DIR}/benchmarks/main.cpp ${HEADERS})

target_link_libraries(PCO_LAB05_tests PRIVATE GTest::GTest GTest::Main ${PCOSYNCHRO_LIB})
target_link_libraries(PCO_LAB05_benchmarks PRIVATE benchmark::benchmark ${PCOSYNCHRO_LIB})

include(GNUInstallDirs)
install(TARGETS PCO_LAB05_tests
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS PCO_LAB05_benchmarks
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
