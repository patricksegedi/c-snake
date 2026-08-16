#include "snake.h"
#include "board.h"
#include "game_types.h"
#include "food.h"
#include "input.h"

static Position snake[MAX_SNAKE_LENGTH];
static Direction snake_direction[MAX_SNAKE_LENGTH];
static Direction direction;
static Direction next_direction;
static int snake_length;

static void draw_snake(void)
{
    for (int i = 0; i < snake_length; i++) {

        if (i == 0)
            board[snake[i].y][snake[i].x] = SNAKE_HEAD;
        else
            board[snake[i].y][snake[i].x] = SNAKE_BODY;
    }
}

static void clear_snake(void)
{
    for (int i = 0; i < snake_length; i++) {
        board[snake[i].y][snake[i].x] = EMPTY;
    }
}

static int hit_wall(void)
{
    if (snake[0].x == 0)
        return 1;

    if (snake[0].x == BOARD_WIDTH - 1)
        return 1;

    if (snake[0].y == 0)
        return 1;

    if (snake[0].y == BOARD_HEIGHT - 1)
        return 1;

    return 0;
}

static int hit_self(void)
{
    for(int i = 1; i < snake_length; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
            return 1;
    }
    return 0;
}

static int ate_food(void)
{
    Position food = get_food_position();

    if (snake[0].x == food.x &&
        snake[0].y == food.y)
        return 1;

    return 0;
}

void init_snake(void)
{
    int center_x = BOARD_WIDTH / 2;
    int center_y = BOARD_HEIGHT / 2;

    snake_length = INITIAL_SNAKE_LENGTH;
    direction = RIGHT;
    next_direction = RIGHT;

    snake[0] = (Position){ center_x, center_y };
    snake[1] = (Position){ center_x - 1, center_y };
    snake[2] = (Position){ center_x - 2, center_y };
    snake[3] = (Position){ center_x - 3, center_y };

    for (int i = 0; i < snake_length; i++) {
        snake_direction[i] = RIGHT;
    }

    draw_snake();
}

MoveResult move_snake(void)
{
    Position old_tail = snake[snake_length - 1];
    clear_snake();

    for (int i = snake_length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
        snake_direction[i] = snake_direction[i - 1];
    }

    direction = get_next_direction();
    next_direction = direction;
    snake_direction[0] = direction;

    switch (direction) {
        case RIGHT:
            snake[0].x++;
            break;

        case LEFT:
            snake[0].x--;
            break;

        case UP:
            snake[0].y--;
            break;

        case DOWN:
            snake[0].y++;
            break;
    }

    if (hit_wall() || hit_self())
        return MOVE_GAME_OVER;

    if (ate_food()) {
        snake[snake_length] = old_tail;
        snake_length++;
        draw_snake();
        spawn_food();
        return MOVE_ATE_FOOD;
    }

    draw_snake();
    return MOVE_OK;
}

void set_direction(Direction new_direction)
{
    if (direction == UP && new_direction == DOWN)
        return;

    if (direction == DOWN && new_direction == UP)
        return;

    if (direction == LEFT && new_direction == RIGHT)
        return;

    if (direction == RIGHT && new_direction == LEFT)
        return;

    next_direction = new_direction;
}

Direction get_direction(void)
{
    return direction;
}

Direction get_segment_direction(int index)
{
    return snake_direction[index];
}

int get_segment_index(Position position)
{
    for (int i = 0; i < snake_length; i++) {

        if (snake[i].x == position.x &&
            snake[i].y == position.y) {

            return i;
        }
    }

    return -1;
}

Position get_segment_position(int index)
{
    return snake[index];
}

int get_snake_length(void)
{
    return snake_length;
}

