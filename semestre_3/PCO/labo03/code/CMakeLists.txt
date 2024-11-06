cmake_minimum_required(VERSION 3.13)
project(PCO_LAB03)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt@5")
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/googletest")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
include_directories(/usr/local/include)
find_library(PCOSYNCHRO_LIB pcosynchro /usr/local/lib)
find_library(GOOGLETEST googletest /usr/local/lib)

find_package(Qt5 COMPONENTS Core Gui Test Widgets)
if (NOT Qt5_FOUND)
    find_package(Qt6 COMPONENTS Core Gui Test Widgets REQUIRED)
endif()

if (Qt5_FOUND)
    add_definitions(-DUSING_QT5)
else()
    add_definitions(-DUSING_QT6)
endif()

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

# Ajoutez les répertoires d'inclusion
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Liste des fichiers sources avec chemins complets
set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/display.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/supplier.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/clinic.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/mainwindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/seller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hospital.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ambulance.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/windowinterface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/main.cpp
        src/utils.cpp
)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/display.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/supplier.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/clinic.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/mainwindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/seller.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hospital.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ambulance.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/iwindowinterface.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/windowinterface.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/fakeinterface.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/costs.h
        src/utils.cpp
)

set(FORMS
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/dialog.ui
)

add_executable(pco_hospital ${SOURCES} ${HEADERS}
        src/utils.cpp)

if (Qt5_FOUND)
    target_link_libraries(pco_hospital PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets ${PCOSYNCHRO_LIB})
else()
    target_link_libraries(pco_hospital PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets ${PCOSYNCHRO_LIB})
endif()

set(SOURCES_TESTS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/display.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/supplier.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/clinic.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/seller.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/mainwindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hospital.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ambulance.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/windowinterface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tests_main.cpp
        src/utils.cpp
)

set(HEADERS_TESTS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/display.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/supplier.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/clinic.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/seller.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/utils.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hospital.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ambulance.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/mainwindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/iwindowinterface.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/windowinterface.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/fakeinterface.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal/costs.h
        src/utils.cpp
)

add_executable(pco_hospital_tests ${SOURCES_TESTS} ${HEADERS_TESTS}
        src/utils.cpp)

if (Qt5_FOUND)
    target_link_libraries(pco_hospital_tests PRIVATE ${GOOGLETEST} Qt5::Core Qt5::Gui Qt5::Test Qt5::Widgets ${PCOSYNCHRO_LIB})
else()
    target_link_libraries(pco_hospital_tests PRIVATE ${GOOGLETEST} Qt6::Core Qt6::Gui Qt6::Test Qt6::Widgets ${PCOSYNCHRO_LIB})
endif()
target_compile_definitions(pco_hospital_tests PRIVATE TESTING_MODE)

file(COPY images/ DESTINATION ${CMAKE_BINARY_DIR}/images/)
