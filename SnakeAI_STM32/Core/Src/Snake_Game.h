#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <stdbool.h>

#define BLOCK_SIZE 8
#define STATE_SIZE 11

typedef enum {
    RIGHT,
    DOWN,
    LEFT,
    UP
} Dir;



void gameInit(void);
void place_food(void);
bool is_collision(int x, int y);
bool is_Food_Eaten(void);
void update_Snake(void);
Dir change_Direction(int action[3]);
void get_state(int state[STATE_SIZE]);
void draw_game(void);
void get_action(float output[3], int action[3]);
void playGame(void);
#endif // SNAKE_GAME_H
