#include "food.h"
#include "board.h"
#include <stdlib.h>

static Position food_position;

void spawn_food(void)
{
    int x;
    int y;

    do {
        x = rand() % (BOARD_WIDTH - 2) + 1;
        y = rand() % (BOARD_HEIGHT - 2) + 1;
    } while (board[y][x] != EMPTY);

    food_position = (Position){ x, y };

    board[food_position.y][food_position.x] = FOOD;
}

Position get_food_position(void)
{
    return food_position;
}