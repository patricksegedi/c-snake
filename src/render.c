#include "render.h"
#include "game_config.h"
#include "board.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
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

    return 1;
}

static void draw_board(void)
{
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {

            if (board[y][x] == WALL) {
                SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
            }
            else if (board[y][x] == SNAKE_HEAD) {
                SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
            }
            else if (board[y][x] == SNAKE_BODY) {
                SDL_SetRenderDrawColor(renderer, 0, 120, 0, 255);
            }
            else if (board[y][x] == FOOD) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            }
            else {
                continue;
            }

            SDL_FRect rect = {
                .x = x * CELL_SIZE,
                .y = y * CELL_SIZE,
                .w = CELL_SIZE,
                .h = CELL_SIZE
            };

            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

static void draw_text(const char *text, float center_x, float y)
{
    SDL_Color color = {255, 255, 255, 255};

    SDL_Surface *surface = TTF_RenderText_Blended(
        font,
        text,
        0,
        color
    );

    if (surface == NULL) {
        printf("Failed to create text surface: %s\n", SDL_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture == NULL) {
        printf("Failed to create text texture: %s\n", SDL_GetError());
        SDL_DestroySurface(surface);
        return;
    }

    SDL_FRect destination = {
        .x = center_x - (float)surface->w / 2.0f,
        .y = y,
        .w = (float)surface->w,
        .h = (float)surface->h
    };

    SDL_RenderTexture(renderer, texture, NULL, &destination);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

static void draw_hud(int score)
{
    char score_text[50];

    snprintf(
        score_text,
        sizeof(score_text),
        "Score: %d",
        score
    );

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);

    SDL_FRect hud = {
        .x = 0,
        .y = GAME_HEIGHT,
        .w = WINDOW_WIDTH,
        .h = HUD_HEIGHT
    };

    SDL_RenderFillRect(renderer, &hud);

    draw_text(score_text, 100, GAME_HEIGHT + 30);
}

void draw_game(int score)
{
    draw_board();
    draw_hud(score);

    SDL_RenderPresent(renderer);
}

void draw_game_over(int score)
{
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    char score_text[50];

    snprintf(
        score_text,
        sizeof(score_text),
        "Final score: %d",
        score
    );

    draw_text("GAME OVER", WINDOW_WIDTH / 2.0f, 200);
    draw_text(score_text, WINDOW_WIDTH / 2.0f, 280);
    draw_text("Press R to restart", WINDOW_WIDTH / 2.0f, 360);
    draw_text("Press Q to quit", WINDOW_WIDTH / 2.0f, 410);

    SDL_RenderPresent(renderer);
}

void cleanup_render(void)
{
    if (font != NULL)
        TTF_CloseFont(font);

    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);

    if (window != NULL)
        SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}