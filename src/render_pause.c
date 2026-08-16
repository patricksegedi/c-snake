#include "render_pause.h"
#include "game_config.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

static void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, SDL_FRect rect);

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

    SDL_Color white = {255, 255, 255, 255};

    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

    SDL_Surface *paused_surface = TTF_RenderText_Blended(font, "PAUSED", 0, white);

    SDL_FRect paused_rect = {
        .x = (GAME_WIDTH - paused_surface->w) / 2.0f,
        .y = GAME_HEIGHT * 0.30f,
        .w = paused_surface->w,
        .h = paused_surface->h
    };

    SDL_DestroySurface(paused_surface);

    draw_text(renderer, font, "PAUSED", white, paused_rect);

    const char *resume_text = "RESUME";
    const char *restart_text = "RESTART";
    const char *quit_text = "QUIT";

    //Resume option block
    if (selected_option == 0)
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    else
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

    SDL_Surface *resume_surface = TTF_RenderText_Blended(font, resume_text, 0, white);

    SDL_FRect resume_rect = {
        .x = (GAME_WIDTH - resume_surface->w) / 2.0f,
        .y = GAME_HEIGHT * 0.45f,
        .w = resume_surface->w,
        .h = resume_surface->h
    };

    SDL_DestroySurface(resume_surface);

    draw_text(renderer, font, resume_text, white, resume_rect);

    // Restart option block
    if (selected_option == 1)
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    else
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

    SDL_Surface *restart_surface = TTF_RenderText_Blended(font, restart_text, 0, white);

    SDL_FRect restart_rect = {
        .x = (GAME_WIDTH - restart_surface->w) / 2.0f,
        .y = GAME_HEIGHT * 0.55f,
        .w = restart_surface->w,
        .h = restart_surface->h
    };

    SDL_DestroySurface(restart_surface);

    draw_text(renderer, font, "RESTART", white, restart_rect);

    //Quit option block
    if (selected_option == 2)
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    else
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

    SDL_Surface *quit_surface = TTF_RenderText_Blended(font, quit_text, 0, white);

    SDL_FRect quit_rect = {
        .x = (GAME_WIDTH - quit_surface->w) / 2.0f,
        .y = GAME_HEIGHT * 0.65f,
        .w = quit_surface->w,
        .h = quit_surface->h
    };

    SDL_DestroySurface(quit_surface);

    draw_text(renderer, font, quit_text, white,quit_rect);

    TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
}

static void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, SDL_FRect rect)
{
    SDL_Surface *surface = TTF_RenderText_Blended(font, text, 0, color);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderTexture(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}