#include "snake_game.h"
#include "lcd.h"
#include <stdlib.h>
#include <time.h>

#define MAX_SNAKE_LENGTH 100
#define OUTPUT_SIZE 3

typedef struct {
    int x;
    int y;
} Point;

static Point snake[MAX_SNAKE_LENGTH];
static int snake_length;
static Dir direction;
static Point food;

void gameInit(void) {

    snake_length = 3;

    snake[0].x = LCD_WIDTH/(2*BLOCK_SIZE);
    snake[0].y = LCD_HEIGHT/(2*BLOCK_SIZE);

    for (int i = 1; i < snake_length; i++) {
        snake[i].x = snake[0].x - i;
        snake[i].y = snake[0].y;
    }

    direction = RIGHT;
    place_food();
    lcd_clear_screen(BLACK);
    draw_game();
    lcd_copy();
}

void place_food(void) {
    int valid = 0;
    while (!valid) {
        food.x = rand() % (LCD_WIDTH / BLOCK_SIZE);
        food.y = rand() % (LCD_HEIGHT / BLOCK_SIZE);

        valid = 1;
        for (int i = 0; i < snake_length; i++) {
            if (snake[i].x == food.x && snake[i].y == food.y) {
                valid = 0;
                break;
            }
        }
    }
}

bool is_collision(int x, int y) {
    if (x < 0 || x >= LCD_WIDTH / BLOCK_SIZE || y < 0 || y >= LCD_HEIGHT / BLOCK_SIZE)
        return true;

    for (int i = 1; i < snake_length; i++) {
        if (snake[i].x == x && snake[i].y == y)
            return true;
    }
    return false;
}

bool is_Food_Eaten(void) {
    return (snake[0].x == food.x && snake[0].y == food.y);
}

void update_Snake(void) {
    int new_x = snake[0].x;
    int new_y = snake[0].y;

    switch (direction) {
        case RIGHT: new_x++; break;
        case LEFT:  new_x--; break;
        case UP:    new_y--; break;
        case DOWN:  new_y++; break;
    }

    if (is_collision(new_x, new_y)) {
        gameInit();
        return;
    }

    for (int i = snake_length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }

    snake[0].x = new_x;
    snake[0].y = new_y;

    if (is_Food_Eaten()) {
        if (snake_length < MAX_SNAKE_LENGTH)
            snake_length++;
        place_food();
    }
}

Dir change_Direction(int action[3]) {

    Dir clock_wise[4] = { RIGHT, DOWN, LEFT, UP };


    int idx = 0;
    for (int i = 0; i < 4; i++) {
        if (clock_wise[i] == direction) {
            idx = i;
            break;
        }
    }

    if (action[0] == 1) {

        direction = clock_wise[idx];
    } else if (action[1] == 1) {

        direction = clock_wise[(idx + 1) % 4];
    } else if (action[2] == 1) {

        direction = clock_wise[(idx + 3) % 4];
    }

    return direction;
}

void get_state(int state[STATE_SIZE]) {
    int x = snake[0].x;
    int y = snake[0].y;

    Point point_l = { x - 1, y };
    Point point_r = { x + 1, y };
    Point point_u = { x, y - 1 };
    Point point_d = { x, y + 1 };

    bool dir_l = direction == LEFT;
    bool dir_r = direction == RIGHT;
    bool dir_u = direction == UP;
    bool dir_d = direction == DOWN;

    // Danger straight
    state[0] = (dir_r && is_collision(point_r.x, point_r.y)) ||
               (dir_l && is_collision(point_l.x, point_l.y)) ||
               (dir_u && is_collision(point_u.x, point_u.y)) ||
               (dir_d && is_collision(point_d.x, point_d.y));

    // Danger right
    state[1] = (dir_u && is_collision(point_r.x, point_r.y)) ||
               (dir_d && is_collision(point_l.x, point_l.y)) ||
               (dir_l && is_collision(point_u.x, point_u.y)) ||
               (dir_r && is_collision(point_d.x, point_d.y));

    // Danger left
    state[2] = (dir_d && is_collision(point_r.x, point_r.y)) ||
               (dir_u && is_collision(point_l.x, point_l.y)) ||
               (dir_r && is_collision(point_u.x, point_u.y)) ||
               (dir_l && is_collision(point_d.x, point_d.y));

    // Current direction
    state[3] = dir_l;
    state[4] = dir_r;
    state[5] = dir_u;
    state[6] = dir_d;

    // Food location
    state[7] = food.x < x;  // food is left
    state[8] = food.x > x;  // food is right
    state[9] = food.y < y;  // food is up
    state[10] = food.y > y; // food is down
}



void draw_game(void) {
    lcd_clear_screen(BLACK);

    for (int i = 0; i < snake_length; i++) {
        int px = snake[i].x * BLOCK_SIZE;
        int py = snake[i].y * BLOCK_SIZE;

        for (int dx = 0; dx < BLOCK_SIZE; dx++) {
            for (int dy = 0; dy < BLOCK_SIZE; dy++) {
                lcd_put_pixel(px + dx, py + dy, GREEN);
            }
        }
    }


    int fx = food.x * BLOCK_SIZE;
    int fy = food.y * BLOCK_SIZE;
    for (int dx = 0; dx < BLOCK_SIZE; dx++) {
        for (int dy = 0; dy < BLOCK_SIZE; dy++) {
            lcd_put_pixel(fx + dx, fy + dy, RED);
        }
    }

    lcd_copy();
}

void get_action(float output[OUTPUT_SIZE], int action[3]) {
    int state[STATE_SIZE];
    get_state(state);

    runAI(state, output);

    int max_i = 0;
    for (int i = 1; i < OUTPUT_SIZE; i++) {
        if (output[i] > output[max_i]) {
            max_i = i;
        }
    }

    for (int i = 0; i < OUTPUT_SIZE; i++) {
        action[i] = (i == max_i) ? 1 : 0;
    }
}


void playGame(void) {
    float output[OUTPUT_SIZE];
    int action[3];

    get_action(output, action);
    change_Direction(action);
    update_Snake();
    draw_game();
}
