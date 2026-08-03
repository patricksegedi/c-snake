#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#define BOARD_WIDTH 40
#define BOARD_HEIGHT 20
#define INITIAL_SNAKE_LENGTH 4
#define MAX_SNAKE_LENGTH ((BOARD_WIDTH - 2) * (BOARD_HEIGHT - 2))

#define MOVE_SPEED 150000

#define WALL '#'
#define EMPTY ' '

#define SNAKE_HEAD 'o'
#define SNAKE_BODY 'x'

#define FOOD '@'

#endif