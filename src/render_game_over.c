#include "render_game_over.h"
#include "render_text.h"
#include "game_config.h"

#include <SDL3_image/SDL_image.h>
#include <stdio.h>

static SDL_Texture *background_texture = NULL;

int init_game_over_render(SDL_Renderer *renderer)
{
    background_texture = IMG_LoadTexture(
        renderer,
        "../assets/images/game_over_background.png"
    );

    if (background_texture == NULL) {
        printf("Failed to load game over background: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

void render_game_over(SDL_Renderer *renderer, TTF_Font *font, int score)
{
    SDL_FRect background = {.x = 0, .y = 0, .w = WINDOW_WIDTH, .h = WINDOW_HEIGHT};
    SDL_RenderTexture(renderer, background_texture, NULL, &background);

    char score_text[50];

    snprintf(
        score_text,
        sizeof(score_text),
        "Final score: %d",
        score
    );

    draw_text(renderer, font, "GAME OVER",
              WINDOW_WIDTH / 2.0f, 200);

    draw_text(renderer, font, score_text,
              WINDOW_WIDTH / 2.0f, 280);

    draw_text(renderer, font, "Press R to restart",
              WINDOW_WIDTH / 2.0f, 360);

    draw_text(renderer, font, "Press Q to quit",
              WINDOW_WIDTH / 2.0f, 410);

    SDL_RenderPresent(renderer);
}

void cleanup_game_over_render(void)
{
    if (background_texture != NULL)
        SDL_DestroyTexture(background_texture);
}