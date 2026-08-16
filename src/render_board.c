#include "render_board.h"
#include "game_config.h"
#include "board.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

static SDL_Texture *background_texture = NULL;

static SDL_Texture *wall_up_texture = NULL;
static SDL_Texture *wall_down_texture = NULL;
static SDL_Texture *wall_left_texture = NULL;
static SDL_Texture *wall_right_texture = NULL;

static SDL_Texture *wall_corner_upper_left_texture = NULL;
static SDL_Texture *wall_corner_upper_right_texture = NULL;
static SDL_Texture *wall_corner_lower_left_texture = NULL;
static SDL_Texture *wall_corner_lower_right_texture = NULL;

static SDL_Texture *get_wall_texture(int x, int y);

int init_board_render(SDL_Renderer *renderer)
{
    const char *paths[] = {
        "../assets/images/background.png",
        "../assets/images/wall_up.png",
        "../assets/images/wall_down.png",
        "../assets/images/wall_left.png",
        "../assets/images/wall_right.png",
        "../assets/images/wall_corner_upper_left.png",
        "../assets/images/wall_corner_upper_right.png",
        "../assets/images/wall_corner_lower_left.png",
        "../assets/images/wall_corner_lower_right.png"
    };

    SDL_Texture **textures[] = {
        &background_texture,
        &wall_up_texture,
        &wall_down_texture,
        &wall_left_texture,
        &wall_right_texture,
        &wall_corner_upper_left_texture,
        &wall_corner_upper_right_texture,
        &wall_corner_lower_left_texture,
        &wall_corner_lower_right_texture
    };

    size_t texture_count = sizeof(textures) / sizeof(textures[0]);

    for (size_t i = 0; i < texture_count; i++) {

        *textures[i] = IMG_LoadTexture(renderer, paths[i]);

        if (*textures[i] == NULL) {
            printf("Failed to load board texture: %s\n", paths[i]);
            return 0;
        }
    }

    return 1;
}

void draw_board(SDL_Renderer *renderer)
{
    SDL_FRect background = {
        .x = 0,
        .y = 0,
        .w = GAME_WIDTH,
        .h = GAME_HEIGHT
    };

    SDL_RenderTexture(
        renderer,
        background_texture,
        NULL,
        &background
    );

    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {

            if (board[y][x] == WALL) {

                SDL_FRect rect = {
                    .x = x * CELL_SIZE,
                    .y = y * CELL_SIZE,
                    .w = CELL_SIZE,
                    .h = CELL_SIZE
                };

                SDL_RenderTexture(
                    renderer,
                    get_wall_texture(x, y),
                    NULL,
                    &rect
                );
            }
        }
    }
}

static SDL_Texture *get_wall_texture(int x, int y)
{
    int top = (y == 0);
    int bottom = (y == BOARD_HEIGHT - 1);
    int left = (x == 0);
    int right = (x == BOARD_WIDTH - 1);

    if (top && left)
        return wall_corner_upper_left_texture;

    if (top && right)
        return wall_corner_upper_right_texture;

    if (bottom && left)
        return wall_corner_lower_left_texture;

    if (bottom && right)
        return wall_corner_lower_right_texture;

    if (top)
        return wall_up_texture;

    if (bottom)
        return wall_down_texture;

    if (left)
        return wall_left_texture;

    if (right)
        return wall_right_texture;

    return wall_up_texture;
}

void cleanup_board_render(void)
{
    if (background_texture != NULL)
        SDL_DestroyTexture(background_texture);

    if (wall_up_texture != NULL)
        SDL_DestroyTexture(wall_up_texture);

    if (wall_down_texture != NULL)
        SDL_DestroyTexture(wall_down_texture);

    if (wall_left_texture != NULL)
        SDL_DestroyTexture(wall_left_texture);

    if (wall_right_texture != NULL)
        SDL_DestroyTexture(wall_right_texture);

    if (wall_corner_upper_left_texture != NULL)
        SDL_DestroyTexture(wall_corner_upper_left_texture);

    if (wall_corner_upper_right_texture != NULL)
        SDL_DestroyTexture(wall_corner_upper_right_texture);

    if (wall_corner_lower_left_texture != NULL)
        SDL_DestroyTexture(wall_corner_lower_left_texture);

    if (wall_corner_lower_right_texture != NULL)
        SDL_DestroyTexture(wall_corner_lower_right_texture);
}