cmake_minimum_required(VERSION 3.20)

project(indigo)

set(CMAKE_MSVC_RUNTIME_LIBRARY
    "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/tests/*.c"
    "${CMAKE_SOURCE_DIR}/tests/*.cpp"
    "${CMAKE_SOURCE_DIR}/utils/*.c"
    "${CMAKE_SOURCE_DIR}/utils/*.cpp"
    "${CMAKE_SOURCE_DIR}/cli/*.c"
    "${CMAKE_SOURCE_DIR}/cli/*.cpp"
    "${CMAKE_SOURCE_DIR}/operation/*.c"
    "${CMAKE_SOURCE_DIR}/operation/*.cpp"
)

add_executable(indigo ${SOURCES})

target_include_directories(indigo PRIVATE
    "${CMAKE_SOURCE_DIR}"
)