cmake_minimum_required(VERSION 3.20)

project(c-snake LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

add_executable(c-snake
    src/main.c
    src/game.c
    src/render_text.c
    src/render_board.c
    src/render_food.c
    src/render_snake.c
    src/render_hud.c

    src/render_game_over.c

    src/render.c
    src/board.c
    src/snake.c
    src/food.c
    src/input.c

    src/pause.c
    src/render_pause.c
    src/input_pause.c

)

target_include_directories(c-snake PRIVATE include)

target_link_libraries(c-snake PRIVATE
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
    SDL3_image::SDL3_image
)