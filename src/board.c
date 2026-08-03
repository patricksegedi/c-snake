#include "board.h"
#include "snake.h"
#include "food.h"

char board[BOARD_HEIGHT][BOARD_WIDTH];

void init_board(void)
{
    for (int y = 0; y < BOARD_HEIGHT; y++) {

        for (int x = 0; x < BOARD_WIDTH; x++) {

            if (x == 0 || x == BOARD_WIDTH - 1 || y == 0 || y == BOARD_HEIGHT - 1)
                board[y][x] = WALL;
            else
                board[y][x] = EMPTY;
        }
    }
}