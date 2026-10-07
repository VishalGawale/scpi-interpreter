cmake_minimum_required(VERSION 3.20)
project(scpi_interpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(scpi_lib
    src/parser.cpp
    src/instrument.cpp
    src/interpreter.cpp
)

target_include_directories(scpi_lib PUBLIC include)
target_compile_options(scpi_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(scpi src/main.cpp)
target_link_libraries(scpi PRIVATE scpi_lib)

enable_testing()
add_subdirectory(tests)