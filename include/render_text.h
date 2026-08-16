#ifndef RENDER_TEXT_H
#define RENDER_TEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

void draw_text(
    SDL_Renderer *renderer,
    TTF_Font *font,
    const char *text,
    float center_x,
    float y
);

#endif