cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(brevm)

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/tests/*.cpp"
    "${CMAKE_SOURCE_DIR}/depends/*.cpp"
)

add_executable(brevm ${SOURCES})

target_include_directories(brevm PRIVATE
    "${CMAKE_SOURCE_DIR}"
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

