#include "render_pause.h"
#include "game_config.h"
#include "render_text.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

void draw_pause_screen(SDL_Renderer *renderer, TTF_Font *font, int selected_option)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 160);

    SDL_FRect overlay = {
        .x = 0,
        .y = 0,
        .w = GAME_WIDTH,
        .h = GAME_HEIGHT
    };

    SDL_RenderFillRect(renderer, &overlay);

    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

    draw_text(renderer, font, "PAUSED", GAME_WIDTH / 2.0f, GAME_HEIGHT * 0.30f);

    if (selected_option == 0)
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    else
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

    draw_text(renderer, font, "RESUME", GAME_WIDTH / 2.0f, GAME_HEIGHT * 0.45f);

    if (selected_option == 1)
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    else
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

    draw_text(renderer, font, "RESTART", GAME_WIDTH / 2.0f, GAME_HEIGHT * 0.55f);

    if (selected_option == 2)
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    else
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

    draw_text(renderer, font, "QUIT", GAME_WIDTH / 2.0f, GAME_HEIGHT * 0.65f);

    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
}