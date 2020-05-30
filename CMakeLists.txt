cmake_minimum_required(VERSION 3.5)

project(Flood-It_A LANGUAGES C)

include_directories("./src")

file(GLOB_RECURSE SOURCES ./src/*.c ./src/*.h)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
link_libraries(${SDL2_LIBRARIES})

add_executable(Flood-It_A ${SOURCES})
target_compile_options(Flood-It_A PUBLIC -Wall -Wextra -pedantic)