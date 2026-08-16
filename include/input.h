#ifndef INPUT_H
#define INPUT_H

#include "game_types.h"

void init_input(void);
void handle_input(void);
int pause_game(void);
int restart_game(void);
int quit_game(void);

Direction get_next_direction(void);

#endif