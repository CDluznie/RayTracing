cmake_minimum_required(VERSION 2.8)

project(raytracer)

set(EXECUTABLE_OUTPUT_PATH bin/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -std=c++17")

include_directories(
        include/
)

file(GLOB_RECURSE SOURCE_FILES src/*)
file(GLOB HEADER_FILES *.hpp)

add_executable(
        raytracer
        ${SOURCE_FILES}
        ${HEADER_FILES}
)

target_link_libraries(
        raytracer
)

