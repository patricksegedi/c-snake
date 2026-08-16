#include "render_snake.h"
#include "snake.h"
#include "board.h"
#include "game_config.h"

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

static SDL_Texture *snake_head_up_texture = NULL;
static SDL_Texture *snake_head_down_texture = NULL;
static SDL_Texture *snake_head_left_texture = NULL;
static SDL_Texture *snake_head_right_texture = NULL;

static SDL_Texture *snake_body_horizontal_left_texture = NULL;
static SDL_Texture *snake_body_horizontal_right_texture = NULL;
static SDL_Texture *snake_body_vertical_up_texture = NULL;
static SDL_Texture *snake_body_vertical_down_texture = NULL;

static SDL_Texture *snake_corner_right_up_texture = NULL;
static SDL_Texture *snake_corner_up_right_texture = NULL;
static SDL_Texture *snake_corner_left_up_texture = NULL;
static SDL_Texture *snake_corner_up_left_texture = NULL;
static SDL_Texture *snake_corner_right_down_texture = NULL;
static SDL_Texture *snake_corner_down_right_texture = NULL;
static SDL_Texture *snake_corner_left_down_texture = NULL;
static SDL_Texture *snake_corner_down_left_texture = NULL;

static SDL_Texture *snake_tail_up_texture = NULL;
static SDL_Texture *snake_tail_down_texture = NULL;
static SDL_Texture *snake_tail_left_texture = NULL;
static SDL_Texture *snake_tail_right_texture = NULL;

static SDL_Texture *get_head_texture(void);
static SDL_Texture *get_body_texture(int index);
static SDL_Texture *get_corner_texture(int index);
static SDL_Texture *get_tail_texture(void);

int init_snake_render(SDL_Renderer *renderer)
{
    const char *paths[] = {
        "../assets/images/snake_head_up.png",
        "../assets/images/snake_head_down.png",
        "../assets/images/snake_head_left.png",
        "../assets/images/snake_head_right.png",

        "../assets/images/snake_body_horizontal_left.png",
        "../assets/images/snake_body_horizontal_right.png",
        "../assets/images/snake_body_vertical_up.png",
        "../assets/images/snake_body_vertical_down.png",

        "../assets/images/snake_corner_right_up.png",
        "../assets/images/snake_corner_up_right.png",
        "../assets/images/snake_corner_left_up.png",
        "../assets/images/snake_corner_up_left.png",
        "../assets/images/snake_corner_right_down.png",
        "../assets/images/snake_corner_down_right.png",
        "../assets/images/snake_corner_left_down.png",
        "../assets/images/snake_corner_down_left.png",

        "../assets/images/snake_tail_up.png",
        "../assets/images/snake_tail_down.png",
        "../assets/images/snake_tail_left.png",
        "../assets/images/snake_tail_right.png"
    };

    SDL_Texture **textures[] = {
        &snake_head_up_texture,
        &snake_head_down_texture,
        &snake_head_left_texture,
        &snake_head_right_texture,

        &snake_body_horizontal_left_texture,
        &snake_body_horizontal_right_texture,
        &snake_body_vertical_up_texture,
        &snake_body_vertical_down_texture,

        &snake_corner_right_up_texture,
        &snake_corner_up_right_texture,
        &snake_corner_left_up_texture,
        &snake_corner_up_left_texture,
        &snake_corner_right_down_texture,
        &snake_corner_down_right_texture,
        &snake_corner_left_down_texture,
        &snake_corner_down_left_texture,

        &snake_tail_up_texture,
        &snake_tail_down_texture,
        &snake_tail_left_texture,
        &snake_tail_right_texture
    };

    size_t texture_count = sizeof(textures) / sizeof(textures[0]);

    for (size_t i = 0; i < texture_count; i++) {
        *textures[i] = IMG_LoadTexture(renderer, paths[i]);

        if (*textures[i] == NULL) {
            printf("Failed to load snake texture: %s\n", paths[i]);
            return 0;
        }
    }

    return 1;
}

void draw_snake(SDL_Renderer *renderer)
{
    int length = get_snake_length();

    for (int i = 0; i < length; i++) {

        Position position = get_segment_position(i);

        if (board[position.y][position.x] == WALL)
            continue;

        SDL_FRect rect = {
            .x = position.x * CELL_SIZE,
            .y = position.y * CELL_SIZE,
            .w = CELL_SIZE,
            .h = CELL_SIZE
        };

        SDL_Texture *texture;

        if (i == 0) {
            texture = get_head_texture();
        }
        else if (i == length - 1) {
            texture = get_tail_texture();
        }
        else {
            texture = get_corner_texture(i);

            if (texture == NULL)
                texture = get_body_texture(i);
        }

        SDL_RenderTexture(renderer, texture, NULL, &rect);
    }
}

void cleanup_snake_render(void)
{
    if (snake_head_up_texture != NULL)
        SDL_DestroyTexture(snake_head_up_texture);

    if (snake_head_down_texture != NULL)
        SDL_DestroyTexture(snake_head_down_texture);

    if (snake_head_left_texture != NULL)
        SDL_DestroyTexture(snake_head_left_texture);

    if (snake_head_right_texture != NULL)
        SDL_DestroyTexture(snake_head_right_texture);

    if (snake_body_horizontal_left_texture != NULL)
        SDL_DestroyTexture(snake_body_horizontal_left_texture);

    if (snake_body_horizontal_right_texture != NULL)
        SDL_DestroyTexture(snake_body_horizontal_right_texture);

    if (snake_body_vertical_up_texture != NULL)
        SDL_DestroyTexture(snake_body_vertical_up_texture);

    if (snake_body_vertical_down_texture != NULL)
        SDL_DestroyTexture(snake_body_vertical_down_texture);

    if (snake_corner_right_up_texture != NULL)
        SDL_DestroyTexture(snake_corner_right_up_texture);

    if (snake_corner_up_right_texture != NULL)
        SDL_DestroyTexture(snake_corner_up_right_texture);

    if (snake_corner_left_up_texture != NULL)
        SDL_DestroyTexture(snake_corner_left_up_texture);

    if (snake_corner_up_left_texture != NULL)
        SDL_DestroyTexture(snake_corner_up_left_texture);

    if (snake_corner_right_down_texture != NULL)
        SDL_DestroyTexture(snake_corner_right_down_texture);

    if (snake_corner_down_right_texture != NULL)
        SDL_DestroyTexture(snake_corner_down_right_texture);

    if (snake_corner_left_down_texture != NULL)
        SDL_DestroyTexture(snake_corner_left_down_texture);

    if (snake_corner_down_left_texture != NULL)
        SDL_DestroyTexture(snake_corner_down_left_texture);

    if (snake_tail_up_texture != NULL)
        SDL_DestroyTexture(snake_tail_up_texture);

    if (snake_tail_down_texture != NULL)
        SDL_DestroyTexture(snake_tail_down_texture);

    if (snake_tail_left_texture != NULL)
        SDL_DestroyTexture(snake_tail_left_texture);

    if (snake_tail_right_texture != NULL)
        SDL_DestroyTexture(snake_tail_right_texture);
}

static SDL_Texture *get_head_texture(void)
{
    switch (get_direction()) {

        case UP:
            return snake_head_up_texture;

        case DOWN:
            return snake_head_down_texture;

        case LEFT:
            return snake_head_left_texture;

        case RIGHT:
            return snake_head_right_texture;
    }

    return snake_head_right_texture;
}

static SDL_Texture *get_body_texture(int index)
{
    switch (get_segment_direction(index)) {

        case UP:
            return snake_body_vertical_up_texture;

        case DOWN:
            return snake_body_vertical_down_texture;

        case LEFT:
            return snake_body_horizontal_left_texture;

        case RIGHT:
            return snake_body_horizontal_right_texture;
    }

    return snake_body_horizontal_right_texture;
}

static SDL_Texture *get_corner_texture(int index)
{
    if (index <= 0 || index >= get_snake_length() - 1)
        return NULL;

    Position previous = get_segment_position(index - 1);
    Position current = get_segment_position(index);
    Position next = get_segment_position(index + 1);

    int incoming_dx = current.x - next.x;
    int incoming_dy = current.y - next.y;

    int outgoing_dx = previous.x - current.x;
    int outgoing_dy = previous.y - current.y;

    if (incoming_dx == 1 && outgoing_dy == -1)
        return snake_corner_right_up_texture;

    if (incoming_dy == -1 && outgoing_dx == 1)
        return snake_corner_up_right_texture;

    if (incoming_dx == -1 && outgoing_dy == -1)
        return snake_corner_left_up_texture;

    if (incoming_dy == -1 && outgoing_dx == -1)
        return snake_corner_up_left_texture;

    if (incoming_dx == 1 && outgoing_dy == 1)
        return snake_corner_right_down_texture;

    if (incoming_dy == 1 && outgoing_dx == 1)
        return snake_corner_down_right_texture;

    if (incoming_dx == -1 && outgoing_dy == 1)
        return snake_corner_left_down_texture;

    if (incoming_dy == 1 && outgoing_dx == -1)
        return snake_corner_down_left_texture;

    return NULL;
}

static SDL_Texture *get_tail_texture(void)
{
    int tail_index = get_snake_length() - 1;

    Position tail = get_segment_position(tail_index);
    Position previous = get_segment_position(tail_index - 1);

    if (previous.x < tail.x)
        return snake_tail_left_texture;

    if (previous.x > tail.x)
        return snake_tail_right_texture;

    if (previous.y < tail.y)
        return snake_tail_up_texture;

    if (previous.y > tail.y)
        return snake_tail_down_texture;

    return snake_tail_right_texture;
}