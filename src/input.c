#include "input.h"
#include "snake.h"
#include "input_pause.h"
#include <SDL3/SDL.h>

#define INPUT_BUFFER_SIZE 2

static int quit_requested;
static int game_paused;
static int restart_requested;

static Direction input_buffer[INPUT_BUFFER_SIZE];
static int input_count;

static void queue_direction(Direction new_direction);

void init_input(void)
{
    quit_requested = 0;
    restart_requested = 0;
    game_paused = 0;
    input_count = 0;

    init_pause_input();
}

int pause_game(void)
{
    return game_paused;
}

int restart_game(void)
{
    return restart_requested;
}

int quit_game(void)
{
    return quit_requested;
}

void handle_input(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_EVENT_QUIT) {
            quit_requested = 1;
        }

        if (event.type != SDL_EVENT_KEY_DOWN)
            continue;

        if (game_paused) {

            int result = handle_pause_input(event.key.key);

            if (result == 0)
                game_paused = 0;

            if (result == 1)
                restart_requested = 1;

            if (result == 2)
                quit_requested = 1;

            continue;
        }

        switch (event.key.key) {

            case SDLK_RETURN:
                game_paused = 1;
                break;

            case SDLK_UP:
                queue_direction(UP);
                break;

            case SDLK_DOWN:
                queue_direction(DOWN);
                break;

            case SDLK_LEFT:
                queue_direction(LEFT);
                break;

            case SDLK_RIGHT:
                queue_direction(RIGHT);
                break;
        }
    }
}

Direction get_next_direction(void)
{
    if (input_count == 0)
        return get_direction();

    Direction next = input_buffer[0];

    for (int i = 1; i < input_count; i++) {
        input_buffer[i - 1] = input_buffer[i];
    }

    input_count--;

    return next;
}

static void queue_direction(Direction new_direction)
{
    if ((get_direction() == UP && new_direction == DOWN) ||
        (get_direction() == DOWN && new_direction == UP) ||
        (get_direction() == LEFT && new_direction == RIGHT) ||
        (get_direction() == RIGHT && new_direction == LEFT)) {
        return;
    }

    if (input_count < INPUT_BUFFER_SIZE) {
        input_buffer[input_count] = new_direction;
        input_count++;
    }
}