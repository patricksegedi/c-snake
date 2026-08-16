#include "render_game_over.h"
#include "render_text.h"
#include "game_config.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>

void render_game_over(SDL_Renderer *renderer, TTF_Font *font, int score)
{
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

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