#include "pause.h"
#include "input_pause.h"

static int pause_active;

void init_pause(void)
{
    pause_active = 0;
}

void open_pause(void)
{
    pause_active = 1;
}

int pause_update(SDL_Keycode key)
{
    int result = handle_pause_input(key);

    if (result == 0) {
        pause_active = 0;
    }

    if (result == 1) {
        return 1;
    }

    return 0;
}

int pause_is_active(void)
{
    return pause_active;
}