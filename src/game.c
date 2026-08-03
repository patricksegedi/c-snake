#include "game.h"
#include "render.h"
#include "board.h"
#include "snake.h"
#include "food.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void init_game(void);
static int game_loop(void);
static int game_over_screen(int score);

void run_game(void)
{
    atexit(cleanup_input);
    while (1) {

        init_game();

        int score = game_loop();

        if (!game_over_screen(score))
            return;
    }
}

static void init_game(void)
{
    init_board();
    init_snake();
    spawn_food();
    init_input();
}

static int game_loop(void)
{
    int score = 0;
    int game_over = 0;

    while (1) {
        system("clear");

        handle_input();

        if (quit_game())
            game_over = 1;

        if (!pause_game()) {
            MoveResult result = move_snake();

            switch (result) {
                case MOVE_OK:
                    break;

                case MOVE_ATE_FOOD:
                    score++;
                    break;

                case MOVE_GAME_OVER:
                    game_over = 1;
                    break;
            }
        }

        if (game_over)
            break;

        draw_board();

        if (pause_game())
            printf("PAUSED\n");

        printf("Score: %d\n", score);

        usleep(MOVE_SPEED);
    }

    return score;
}

static int game_over_screen(int score)
{
    system("clear");
    printf("Game Over!\n");
    printf("Final score: %d\n", score);
    printf("Press R to restart\n");
    printf("Press Q to quit\n");

    while (1) {
        char key;

        if (read(STDIN_FILENO, &key, 1) != 1) {
            usleep(10000);
            continue;
        }

        if (key == 'r')
            return 1;

        if (key == 'q')
            return 0;
    }
}