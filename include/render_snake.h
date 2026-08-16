#ifndef RENDER_SNAKE_H
#define RENDER_SNAKE_H

#include <SDL3/SDL.h>

int init_snake_render(SDL_Renderer *renderer);
void draw_snake(SDL_Renderer *renderer);
void cleanup_snake_render(void);

#endif