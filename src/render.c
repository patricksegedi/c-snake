#include "render.h"
#include "render_board.h"
#include "render_hud.h"
#include "render_food.h"
#include "render_snake.h"
#include "render_pause.h"
#include "input.h"
#include "input_pause.h"
#include "render_main_menu.h"
#include "render_game_over.h"
#include "game_config.h"


#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static TTF_Font *font = NULL;


int init_render(void)
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }

    if (!SDL_CreateWindowAndRenderer(
            "C Snake",
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0,
            &window,
            &renderer)) {

        printf("SDL_CreateWindowAndRenderer failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    printf("SDL window created successfully\n");

    if (!TTF_Init()) {
        printf("TTF_Init failed: %s\n", SDL_GetError());
        cleanup_render();
        return 0;
    }

    font = TTF_OpenFont("../assets/fonts/Roboto-Regular.ttf", 32);

    if (font == NULL) {
        printf("TTF_OpenFont failed: %s\n", SDL_GetError());
        cleanup_render();
        return 0;
    }

    if (!init_main_menu_render(renderer)) {
        cleanup_render();
        return 0;
    }

    if (!init_board_render(renderer)) {
        cleanup_render();
        return 0;
    }

    if (!init_hud_render(renderer)) {
        cleanup_render();
        return 0;
    }

    if (!init_snake_render(renderer)) {
        cleanup_render();
        return 0;
    }

    if (!init_food_render(renderer)) {
        cleanup_render();
        return 0;
    }

    if (!init_game_over_render(renderer)) {
        cleanup_render();
        return 0;
    }

    return 1;
}

void draw_main_menu(int selected_option)
{
    SDL_RenderClear(renderer);

    draw_main_menu_screen(renderer, selected_option);

    SDL_RenderPresent(renderer);
}

void draw_game(int score)
{
    draw_board(renderer);
    draw_food(renderer);
    draw_snake(renderer);
    draw_hud(renderer, font, score);

    if (pause_game()) {
        draw_pause_screen(renderer, font, get_pause_selection());
    }

    SDL_RenderPresent(renderer);
}

void draw_game_over(int score)
{
    render_game_over(renderer, font, score);
}

void cleanup_render(void)
{
    if (font != NULL)
        TTF_CloseFont(font);
    
    cleanup_board_render();
    cleanup_hud_render();
    cleanup_food_render();
    cleanup_snake_render();
    cleanup_main_menu_render();
    cleanup_game_over_render();

    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);

    if (window != NULL)
        SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}