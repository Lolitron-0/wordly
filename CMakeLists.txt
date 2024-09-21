cmake_minimum_required(VERSION 3.22)
project(wordly)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall)

include_directories(include)

set(SOURCES src/Dictionary.cpp src/Wordly.cpp src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
