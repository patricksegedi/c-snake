#include "render_main_menu.h"
#include "game_config.h"

#include <SDL3_image/SDL_image.h>
#include <stdio.h>

static SDL_Texture *background_texture = NULL;
static SDL_Texture *logo_texture = NULL;
static SDL_Texture *start_button_texture = NULL;
static SDL_Texture *quit_button_texture = NULL;

int init_main_menu_render(SDL_Renderer *renderer)
{
    const char *paths[] = {
        "../assets/images/main_menu_background.png",
        "../assets/images/game_logo.png",
        "../assets/images/start_button.png",
        "../assets/images/quit_button.png"
    };

    SDL_Texture **textures[] = {
        &background_texture,
        &logo_texture,
        &start_button_texture,
        &quit_button_texture
    };

    size_t texture_count = sizeof(textures) / sizeof(textures[0]);

    for (size_t i = 0; i < texture_count; i++) {

        *textures[i] = IMG_LoadTexture(renderer, paths[i]);

        if (*textures[i] == NULL) {
            printf("Failed to load main menu texture: %s\n", paths[i]);
            cleanup_main_menu_render();
            return 0;
        }
    }

    return 1;
}

void draw_main_menu_screen(SDL_Renderer *renderer, int selected_option)
{
    SDL_FRect background = {.x = 0, .y = 0, .w = WINDOW_WIDTH, .h = WINDOW_HEIGHT};
    SDL_RenderTexture(renderer, background_texture, NULL, &background);

    SDL_FRect logo = {.x = 300, .y = 50, .w = 600, .h = 300};
    SDL_RenderTexture(renderer, logo_texture, NULL, &logo);

    if (selected_option == 0) {
        SDL_FRect start_button = {
            .x = (WINDOW_WIDTH - 200 * 1.1f) / 2.0f,
            .y = 425 - (66 * 0.1f) / 2.0f,
            .w = 200 * 1.1f,
            .h = 66 * 1.1f
        };

        SDL_RenderTexture(renderer, start_button_texture, NULL, &start_button);

        SDL_FRect quit_button = {
            .x = (WINDOW_WIDTH - 200) / 2.0f,
            .y = 500,
            .w = 200,
            .h = 66
        };

        SDL_RenderTexture(renderer, quit_button_texture, NULL, &quit_button);
    }
    else {
        SDL_FRect start_button = {
            .x = (WINDOW_WIDTH - 200) / 2.0f,
            .y = 425,
            .w = 200,
            .h = 66
        };

        SDL_RenderTexture(renderer, start_button_texture, NULL, &start_button);

        SDL_FRect quit_button = {
            .x = (WINDOW_WIDTH - 200 * 1.1f) / 2.0f,
            .y = 500 - (66 * 0.1f) / 2.0f,
            .w = 200 * 1.1f,
            .h = 66 * 1.1f
        };

        SDL_RenderTexture(renderer, quit_button_texture, NULL, &quit_button);
    }
}

void cleanup_main_menu_render(void)
{
    if (background_texture != NULL)
        SDL_DestroyTexture(background_texture);

    if (logo_texture != NULL)
        SDL_DestroyTexture(logo_texture);

    if (start_button_texture != NULL)
        SDL_DestroyTexture(start_button_texture);

    if (quit_button_texture != NULL)
        SDL_DestroyTexture(quit_button_texture);
}