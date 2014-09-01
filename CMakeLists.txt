cmake_minimum_required(VERSION 2.6)

project(oceanskeeper2)

include_directories(flat/src)

file(
    GLOB_RECURSE
    src
    src/*
    flat/src/*
)

set(CMAKE_CXX_FLAGS "-g -Wall")

add_executable(
    ok2
    ${src}
)

target_link_libraries(
    ok2
    SDL2
    SDL2_image
    SDL2_mixer
    SDL2_ttf
    lua5.2
    GL
    GLU
    GLEW
)
