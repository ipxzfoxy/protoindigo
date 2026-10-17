cmake_minimum_required(VERSION 3.20)

project(
    indigo
    VERSION 2.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY
    "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

# Dependencies
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/depends/brevm"
)

# ProtoIndigo Library Sources
file(GLOB_RECURSE INDIGO_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/operation/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/operation/*.cpp"
)

# ProtoIndigo Library
add_library(indigo_lib STATIC
    ${INDIGO_SOURCES}
)

target_include_directories(indigo_lib
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/operation"
        "${CMAKE_CURRENT_SOURCE_DIR}/depends/brevm/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/depends/brevm/depends/brevmr/include"
)

target_link_libraries(indigo_lib
    PUBLIC
        brevm_lib
)

target_compile_definitions(indigo_lib PRIVATE
    INDIGO_VERSION="${PROJECT_VERSION}"
    BREVM_VERSION="${BREVM_VERSION}"
)

# ProtoIndigo CLI Sources
file(GLOB_RECURSE CLI_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/cli/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/cli/*.cpp"
)

# ProtoIndigo CLI
add_executable(indigo
    ${CLI_SOURCES}
    cli/indigo.rc
)

target_include_directories(indigo
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/operation"
        "${CMAKE_CURRENT_SOURCE_DIR}/depends/brevm/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/depends/brevm/depends/brevmr/include"
)

target_link_libraries(indigo
    PRIVATE
        indigo_lib
)

target_compile_definitions(indigo PRIVATE
    INDIGO_VERSION="${PROJECT_VERSION}"
)

# Runtime Files
add_custom_command(TARGET indigo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/scripts"
        "$<TARGET_FILE_DIR:indigo>/scripts"

    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE"
        "$<TARGET_FILE_DIR:indigo>/LICENSE"
)
