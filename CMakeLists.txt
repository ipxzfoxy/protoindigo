cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
        indigo
        LANGUAGES CXX
        VERSION 2.1.0
)

set(CMAKE_MSVC_RUNTIME_LIBRARY
    "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

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
    "${CMAKE_SOURCE_DIR}/depends/brevm/src/*.cpp"
)

add_executable(indigo ${SOURCES}
)

target_compile_definitions(indigo PRIVATE
    INDIGO_VERSION="${PROJECT_VERSION}"
)

add_custom_command(TARGET indigo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/scripts"
        "$<TARGET_FILE_DIR:indigo>/scripts"

    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/LICENSE"
        "$<TARGET_FILE_DIR:indigo>/LICENSE"
)

target_include_directories(indigo PRIVATE
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/operation/include"
    "${CMAKE_SOURCE_DIR}/depends/brevm"
)