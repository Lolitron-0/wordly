cmake_minimum_required(VERSION 3.22)
project(wordly)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall)

include_directories(include)

set(SOURCES src/Dictionary.cpp src/Wordly.cpp src/UIHelper.cpp src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(thirdparty/cxxopts)
target_link_libraries(${PROJECT_NAME} PRIVATE cxxopts)

# for header only
target_include_directories(${PROJECT_NAME} PRIVATE thirdparty)
