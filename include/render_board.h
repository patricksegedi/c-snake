#ifndef RENDER_BOARD_H
#define RENDER_BOARD_H

#include <SDL3/SDL.h>

int init_board_render(SDL_Renderer *renderer);
void draw_board(SDL_Renderer *renderer);
void cleanup_board_render(void);

#endif