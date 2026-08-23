#include "render_food.h"
#include "game_config.h"
#include "food.h"
#include "board.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <math.h>
#include <stdio.h>

static SDL_Texture *apple_texture = NULL;

static float apple_spawn_scale = 1.0f;
static float apple_angle = 0.0f;
static float apple_scale = 1.0f;

static Uint64 apple_spawn_time = 0;
static int last_food_x = -1;
static int last_food_y = -1;

static void update_food_animation(void);

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
    apple_angle = sinf(SDL_GetTicks() * 0.003f) * 5.0f;
    apple_scale = 1.0f + sinf(SDL_GetTicks() * 0.003f) * 0.03f;

    update_food_animation();

    for (int y = 0; y < BOARD_HEIGHT; y++) {

        for (int x = 0; x < BOARD_WIDTH; x++) {

            if (board[y][x] == FOOD) {

                float size = CELL_SIZE * apple_scale * apple_spawn_scale;

                SDL_FRect rect = {
                    .x = x * CELL_SIZE + (CELL_SIZE - size) / 2.0f,
                    .y = y * CELL_SIZE + (CELL_SIZE - size) / 2.0f,
                    .w = size,
                    .h = size
                };

                SDL_RenderTextureRotated(renderer, apple_texture, NULL, &rect, apple_angle, NULL, SDL_FLIP_NONE);
            }
        }
    }
}

void cleanup_food_render(void)
{
    if (apple_texture != NULL)
        SDL_DestroyTexture(apple_texture);
}

static void update_food_animation(void)
{
    Position food_position = get_food_position();

    if (food_position.x != last_food_x ||
        food_position.y != last_food_y) {

        last_food_x = food_position.x;
        last_food_y = food_position.y;

        apple_spawn_time = SDL_GetTicks();
    }

    Uint64 elapsed = SDL_GetTicks() - apple_spawn_time;

    if (elapsed < 300) {
        float progress = elapsed / 300.0f;
        apple_spawn_scale = progress * 1.1f;
    }
    else {
        apple_spawn_scale = 1.0f;
    }
}