#include "main_menu.h"
#include "input_main_menu.h"
#include "render.h"

#include <SDL3/SDL.h>

int run_main_menu(void)
{
    while (1) {
        draw_main_menu(get_main_menu_selection());

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                return 1;

            if (event.type == SDL_EVENT_KEY_DOWN) {
                int result = handle_main_menu_input(event.key.key);

                if (result == 0)
                    return 0;

                if (result == 1)
                    return 1;
            }
        }

        SDL_Delay(16);
    }
}