cmake_minimum_required(VERSION 3.13)
project(PCO_LAB02)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")
find_package(Qt5 COMPONENTS Core Gui Concurrent Widgets)
if (NOT Qt5_FOUND)
    find_package(Qt6 COMPONENTS Core Gui Concurrent Widgets REQUIRED)
endif()

if (Qt5_FOUND)
    add_definitions(-DUSING_QT5)
else()
    add_definitions(-DUSING_QT6)
endif()

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)
include_directories(/usr/local/include)
find_library(PCOSYNCHRO_LIB pcosynchro /usr/local/lib)
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE FORMS "ui/*.ui")

add_executable(pco_bogosort ${SOURCES} ${HEADERS} ${FORMS})

if (Qt5_FOUND)
    #target_link_libraries(pco_bogosort PRIVATE Qt5::Core Qt5::Gui Qt5::Concurrent Qt5::Widgets -lpcosynchro)

    target_link_libraries(pco_bogosort PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Concurrent ${PCOSYNCHRO_LIB})
else()
    #target_link_libraries(pco_bogosort PRIVATE Qt6::Core Qt6::Gui Qt6::Concurrent Qt6::Widgets -lpcosynchro)
    target_link_libraries(pco_bogosort PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Concurrent ${PCOSYNCHRO_LIB})
endif()