#ifndef RENDER_MAIN_MENU_H
#define RENDER_MAIN_MENU_H

#include <SDL3/SDL.h>

int init_main_menu_render(SDL_Renderer *renderer);

void draw_main_menu_screen(SDL_Renderer *renderer, int selected_option);

void cleanup_main_menu_render(void);

#endif