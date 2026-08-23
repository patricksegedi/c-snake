#include "input_main_menu.h"

static int main_menu_selection = 0;

int get_main_menu_selection(void)
{
    return main_menu_selection;
}

int handle_main_menu_input(SDL_Keycode key)
{
    if (key == SDLK_UP) {
        if (main_menu_selection == 0)
            main_menu_selection = 1;
        else
            main_menu_selection--;

        return -1;
    }

    if (key == SDLK_DOWN) {
        if (main_menu_selection == 1)
            main_menu_selection = 0;
        else
            main_menu_selection++;

        return -1;
    }

    if (key == SDLK_RETURN)
        return main_menu_selection;

    return -1;
}