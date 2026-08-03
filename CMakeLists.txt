cmake_minimum_required(VERSION 3.20)

project(c-snake LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

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