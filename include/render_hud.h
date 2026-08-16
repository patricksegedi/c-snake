#ifndef RENDER_HUD_H
#define RENDER_HUD_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

int init_hud_render(SDL_Renderer *renderer);
void draw_hud(SDL_Renderer *renderer, TTF_Font *font, int score);
void cleanup_hud_render(void);

#endif