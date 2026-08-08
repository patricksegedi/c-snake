#include "input.h"
#include "snake.h"
#include <SDL3/SDL.h>


static int quit_requested;
static int game_paused;

void init_input(void)
{
    quit_requested = 0;
    game_paused = 0;
}

int quit_game(void)
{
    return quit_requested;
}

int pause_game(void)
{
    return game_paused;
}

void handle_input(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_EVENT_QUIT) {
            quit_requested = 1;
        }

        if (event.type == SDL_EVENT_KEY_DOWN) {

            switch (event.key.key) {

                case SDLK_Q:
                    quit_requested = 1;
                    break;

                case SDLK_P:
                    game_paused = !game_paused;
                    break;

                case SDLK_W:
                    set_direction(UP);
                    game_paused = 0;
                    break;

                case SDLK_A:
                    set_direction(LEFT);
                    game_paused = 0;
                    break;

                case SDLK_S:
                    set_direction(DOWN);
                    game_paused = 0;
                    break;

                case SDLK_D:
                    set_direction(RIGHT);
                    game_paused = 0;
                    break;
            }
        }
    }
}