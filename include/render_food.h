#ifndef RENDER_FOOD_H
#define RENDER_FOOD_H

#include <SDL3/SDL.h>

int init_food_render(SDL_Renderer *renderer);
void draw_food(SDL_Renderer *renderer);
void cleanup_food_render(void);

#endif