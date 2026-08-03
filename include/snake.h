#ifndef SNAKE_H
#define SNAKE_H

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef enum {
    MOVE_OK,
    MOVE_ATE_FOOD,
    MOVE_GAME_OVER
} MoveResult;

void init_snake(void);
MoveResult move_snake(void);
void set_direction(Direction new_direction);

#endif