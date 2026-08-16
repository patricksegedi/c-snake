#ifndef SNAKE_H
#define SNAKE_H

#include "game_types.h"

typedef enum {
    MOVE_OK,
    MOVE_ATE_FOOD,
    MOVE_GAME_OVER
} MoveResult;

void init_snake(void);
MoveResult move_snake(void);
void set_direction(Direction new_direction);
Direction get_direction(void);
Direction get_segment_direction(int index);
int get_segment_index(Position position);
Position get_segment_position(int index);
int get_snake_length(void);

#endif