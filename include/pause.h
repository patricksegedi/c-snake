#ifndef PAUSE_H
#define PAUSE_H

#include <SDL3/SDL.h>

void init_pause(void);
void open_pause(void);
int pause_update(SDL_Keycode key);
int pause_is_active(void);

#endif