#ifndef GAME_TYPES_H
#define GAME_TYPES_H

typedef struct
{
    int x;
    int y;
} Position;

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef enum {
    GAME_OVER,
    GAME_RESTART
} GameResult;

#endif