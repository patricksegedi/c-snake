#include "render_text.h"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>

void draw_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, float center_x, float y)
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

    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(renderer, surface);

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

    SDL_RenderTexture(
        renderer,
        texture,
        NULL,
        &destination
    );

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}