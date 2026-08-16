#include "input_pause.h"

static int pause_selection = 0;

int get_pause_selection(void)
{
    return pause_selection;
}

int handle_pause_input(SDL_Keycode key)
{
    if (key == SDLK_UP) {
        if (pause_selection == 0)
            pause_selection = 2;
        else
            pause_selection--;
        
        return -1;
    }

    if (key == SDLK_DOWN) {
        if (pause_selection == 2)
            pause_selection = 0;
        else
            pause_selection++;

        return -1;
    }

    if (key == SDLK_RETURN)
        return pause_selection;

    return -1;
}

void init_pause_input(void)
{
    pause_selection = 0;
}