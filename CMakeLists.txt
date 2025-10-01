cmake_minimum_required(VERSION 3.16)

project(QTCALCULATOR VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(QTCALCULATOR
    src/mainwindow.cpp
    src/mainwindow.hpp
    src/calculator.cpp
    src/parser.cpp
    src/parser.hpp
)

target_link_libraries(QTCALCULATOR PRIVATE Qt6::Widgets)

set_target_properties(QTCALCULATOR PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
