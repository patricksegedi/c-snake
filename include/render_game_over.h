#ifndef RENDER_GAME_OVER_H
#define RENDER_GAME_OVER_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

void render_game_over(SDL_Renderer *renderer, TTF_Font *font, int score);

#endif