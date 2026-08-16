#include "render_food.h"
#include "game_config.h"
#include "board.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

static SDL_Texture *apple_texture = NULL;


int init_food_render(SDL_Renderer *renderer)
{
    apple_texture = IMG_LoadTexture(
        renderer,
        "../assets/images/apple.png"
    );

    if (apple_texture == NULL) {
        printf("Failed to load food texture: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}


void draw_food(SDL_Renderer *renderer)
{
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {

            if (board[y][x] == FOOD) {

                SDL_FRect rect = {
                    .x = x * CELL_SIZE,
                    .y = y * CELL_SIZE,
                    .w = CELL_SIZE,
                    .h = CELL_SIZE
                };

                SDL_RenderTexture(
                    renderer,
                    apple_texture,
                    NULL,
                    &rect
                );
            }
        }
    }
}

void cleanup_food_render(void)
{
    if (apple_texture != NULL)
        SDL_DestroyTexture(apple_texture);
}