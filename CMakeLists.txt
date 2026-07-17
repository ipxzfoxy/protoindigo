cmake_minimum_required(VERSION 3.20)

project(indigo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/tests/*.c"
    "${CMAKE_SOURCE_DIR}/tests/*.cpp"
    "${CMAKE_SOURCE_DIR}/utils/*.c"
    "${CMAKE_SOURCE_DIR}/utils/*.cpp"
)
if(WIN32)
    set(APP_ICON "${CMAKE_SOURCE_DIR}/resources/app.rc")
endif()

add_executable(indigo
    ${APP_ICON} ${SOURCES}
)