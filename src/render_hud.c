#include "render_hud.h"
#include "render_text.h"
#include "game_config.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

static SDL_Texture *hud_wall_left_texture = NULL;
static SDL_Texture *hud_wall_right_texture = NULL;
static SDL_Texture *hud_wall_down_texture = NULL;

static SDL_Texture *hud_corner_lower_left_texture = NULL;
static SDL_Texture *hud_corner_lower_right_texture = NULL;

static void draw_hud_walls(SDL_Renderer *renderer);

int init_hud_render(SDL_Renderer *renderer)
{
    const char *paths[] = {
        "../assets/images/hud_wall_left.png",
        "../assets/images/hud_wall_right.png",
        "../assets/images/hud_wall_down.png",
        "../assets/images/hud_corner_lower_left.png",
        "../assets/images/hud_corner_lower_right.png"
    };

    SDL_Texture **textures[] = {
        &hud_wall_left_texture,
        &hud_wall_right_texture,
        &hud_wall_down_texture,
        &hud_corner_lower_left_texture,
        &hud_corner_lower_right_texture
    };

    size_t texture_count = sizeof(textures) / sizeof(textures[0]);

    for (size_t i = 0; i < texture_count; i++) {

        *textures[i] = IMG_LoadTexture(renderer, paths[i]);

        if (*textures[i] == NULL) {
            printf("Failed to load HUD texture: %s\n", paths[i]);
            return 0;
        }
    }

    return 1;
}

void draw_hud(SDL_Renderer *renderer, TTF_Font *font, int score)
{
    char score_text[50];

    snprintf(score_text, sizeof(score_text), "Score: %d", score);

    SDL_SetRenderDrawColor(renderer, 53, 53, 56, 255);

    SDL_FRect hud = {
        .x = 0,
        .y = GAME_HEIGHT,
        .w = WINDOW_WIDTH,
        .h = HUD_HEIGHT
    };

    SDL_RenderFillRect(renderer, &hud);

    draw_text(renderer, font, score_text, 100, GAME_HEIGHT + 25);
    draw_hud_walls(renderer);
}

static void draw_hud_walls(SDL_Renderer *renderer)
{
    SDL_FRect lower_left_corner = {
        .x = 0,
        .y = WINDOW_HEIGHT - CELL_SIZE,
        .w = CELL_SIZE,
        .h = CELL_SIZE
    };

    SDL_RenderTexture(renderer, hud_corner_lower_left_texture, NULL, &lower_left_corner);

    SDL_FRect lower_right_corner = {
        .x = WINDOW_WIDTH - CELL_SIZE,
        .y = WINDOW_HEIGHT - CELL_SIZE,
        .w = CELL_SIZE,
        .h = CELL_SIZE
    };

    SDL_RenderTexture(renderer, hud_corner_lower_right_texture, NULL, &lower_right_corner);

    SDL_FRect left_wall = {
        .x = 0,
        .y = GAME_HEIGHT,
        .w = CELL_SIZE,
        .h = HUD_HEIGHT - CELL_SIZE
    };

    SDL_RenderTexture(renderer, hud_wall_left_texture, NULL, &left_wall);

    SDL_FRect right_wall = {
        .x = WINDOW_WIDTH - CELL_SIZE,
        .y = GAME_HEIGHT,
        .w = CELL_SIZE,
        .h = HUD_HEIGHT - CELL_SIZE
    };

    SDL_RenderTexture(renderer, hud_wall_right_texture, NULL, &right_wall);

    SDL_FRect bottom_wall = {
        .x = CELL_SIZE,
        .y = WINDOW_HEIGHT - CELL_SIZE,
        .w = WINDOW_WIDTH - (2 * CELL_SIZE),
        .h = CELL_SIZE
    };

    SDL_RenderTexture(renderer, hud_wall_down_texture, NULL, &bottom_wall);
}

void cleanup_hud_render(void)
{
    if (hud_wall_left_texture != NULL)
        SDL_DestroyTexture(hud_wall_left_texture);

    if (hud_wall_right_texture != NULL)
        SDL_DestroyTexture(hud_wall_right_texture);

    if (hud_wall_down_texture != NULL)
        SDL_DestroyTexture(hud_wall_down_texture);

    if (hud_corner_lower_left_texture != NULL)
        SDL_DestroyTexture(hud_corner_lower_left_texture);

    if (hud_corner_lower_right_texture != NULL)
        SDL_DestroyTexture(hud_corner_lower_right_texture);
}