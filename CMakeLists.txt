cmake_minimum_required(VERSION 3.16)

project(propositional_parser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_path(CLI11_INCLUDE_DIR CLI/CLI.hpp)
if(NOT CLI11_INCLUDE_DIR)
    message(FATAL_ERROR "CLI11 headers not found. Install CLI11 or set CLI11_INCLUDE_DIR.")
endif()

add_library(propositional_parser
    src/compare.cpp
    src/evaluator.cpp
    src/lexer.cpp
    src/postfix.cpp
    src/truthTableGenerator.cpp
    src/varNamesCollector.cpp
)

target_include_directories(propositional_parser
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(parser src/main.cpp)

target_include_directories(parser PRIVATE ${CLI11_INCLUDE_DIR})
target_link_libraries(parser PRIVATE propositional_parser)
