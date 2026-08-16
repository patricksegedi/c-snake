#ifndef RENDER_PAUSE_H
#define RENDER_PAUSE_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

void draw_pause_screen(SDL_Renderer *renderer, TTF_Font *font, int selected_option);

#endif