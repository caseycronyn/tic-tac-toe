#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// allocate space and initialise all positions to ' '
char * init_board(void);
bool play_turn(char player_c, char *player_s, char *location);
void print_board(char *location);
bool check_winner(char x, char *location);
bool check_end(char *location);
void test(void);
