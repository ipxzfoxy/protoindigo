cmake_minimum_required(VERSION 3.20)

project(
    brevm
    VERSION 0.0.2
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE BREVM_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)


add_library(brevm_lib STATIC
    ${BREVM_SOURCES}
)

target_compile_definitions(brevm_lib PUBLIC
        BREVM_VERSION="${PROJECT_VERSION}"
)

target_include_directories(brevm_lib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/depends/brevm-reference"
)