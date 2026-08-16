#ifndef INPUT_PAUSE_H
#define INPUT_PAUSE_H

#include <SDL3/SDL.h>

int get_pause_selection(void);
int handle_pause_input(SDL_Keycode key);
void init_pause_input(void);

#endif