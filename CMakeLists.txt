cmake_minimum_required(VERSION 3.20)

project(c-snake LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

add_executable(c-snake
    src/main.c
    src/game.c
    src/render.c
    src/board.c
    src/snake.c
    src/food.c
    src/input.c
)

target_include_directories(c-snake PRIVATE include)

target_link_libraries(c-snake PRIVATE
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
)