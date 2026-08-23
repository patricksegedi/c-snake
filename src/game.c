#include "game.h"
#include "render.h"
#include "audio.h"
#include "board.h"
#include "snake.h"
#include "food.h"
#include "input.h"
#include "pause.h"
#include "main_menu.h"
#include "game_types.h"
#include <SDL3/SDL.h>

static void init_game(void);
static GameResult game_loop(int *score);
static int game_over_screen(int score);

void run_game(void)
{
    if (!init_render())
        return;
    
    if (!init_audio()) {
        cleanup_render();
        return;
    }

    if (run_main_menu() == 1) {
        cleanup_audio();
        cleanup_render();
        return;
    }

    while (1) {

        play_gameplay_music();

        init_game();

        int score = 0;

        GameResult result = game_loop(&score);

        if (result == GAME_RESTART)
            continue;

        if (!game_over_screen(score))
            break;
    }

    cleanup_audio();
    cleanup_render();
}

static void init_game(void)
{
    init_board();
    init_snake();
    spawn_food();
    init_input();
}

static GameResult game_loop(int *score)
{
    int game_over = 0;
    int was_paused = 0;

    Uint64 last_move = SDL_GetTicks();

    while (!game_over) {

        handle_input();

        if (pause_game()) {

            if (!was_paused) {
                pause_gameplay_music();
                was_paused = 1;
            }

        } else {

            if (was_paused) {
                resume_gameplay_music();
                was_paused = 0;
            }
        }

        if (quit_game()) {
            game_over = 1;
            continue;
        }

        if (restart_game())
            return GAME_RESTART;

        Uint64 current_time = SDL_GetTicks();

        if (!pause_game() && current_time - last_move >= MOVE_INTERVAL) {

            MoveResult result = move_snake();

            switch (result) {
                case MOVE_OK:
                    break;

                case MOVE_ATE_FOOD:
                    play_eat_sound();
                    (*score)++;
                    break;

                case MOVE_GAME_OVER:
                    game_over = 1;
                    break;
            }

            last_move = current_time;
        }

        draw_game(*score);

        SDL_Delay(16);
    }

    stop_gameplay_music();

    return GAME_OVER;
}

static int game_over_screen(int score)
{
    draw_game_over(score);

    while (1) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_EVENT_QUIT)
                return 0;

            if (event.type == SDL_EVENT_KEY_DOWN) {

                if (event.key.key == SDLK_R)
                    return 1;

                if (event.key.key == SDLK_Q)
                    return 0;
            }
        }

        SDL_Delay(16);
    }
}