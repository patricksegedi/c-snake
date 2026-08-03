#include "input.h"
#include "snake.h"

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

static struct termios original_termios;
static int quit_requested;
static int game_paused;

void init_input(void)
{
    quit_requested = 0;
    game_paused = 0;
    
    tcgetattr(STDIN_FILENO, &original_termios);

    struct termios raw = original_termios;

    raw.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void cleanup_input(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
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
    char key;

    if (read(STDIN_FILENO, &key, 1) != 1)
        return;
    
    switch (key) {
        case 'q':
            quit_requested = 1;
            break;

        case 'p':
            game_paused = !game_paused;
            break;

        case 'w':
            set_direction(UP);
            game_paused = 0;
            break;
            
        case 'a':
            set_direction(LEFT);
            game_paused = 0;
            break;

        case 's':
            set_direction(DOWN);
            game_paused = 0;
            break;

        case 'd':
            set_direction(RIGHT);
            game_paused = 0;
            break;
    }
}