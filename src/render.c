#include "render.h"
#include "game_config.h"
#include "board.h"
#include <stdio.h>

void draw_board(void)
{
    for (int y = 0; y < BOARD_HEIGHT; y++) {

        for (int x = 0; x < BOARD_WIDTH; x++) {

            printf("%c", board[y][x]);
        }
        
        printf("\n");
    }
}