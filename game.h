#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define BIGSTRING 30
#define BOARDSIZE 3
#define EMPTY ' '
#define GAMEOVER 9

typedef struct {
   char piece;
   char name[BIGSTRING];
} player;

// initialise all positions to ' '
void init_board(char board[][BOARDSIZE]);
bool play_turn(player * plyr, char board[][BOARDSIZE], int * move);
void print_board(char board[][BOARDSIZE]);
// returns name of winner or NULL if none
bool check_winner(char a, char board[][BOARDSIZE]);
// loops over play turn until finished
int * get_move(char * name, char board[][BOARDSIZE], int * move);
bool check_rows_and_cols(char x, char loc[][BOARDSIZE]);
bool check_diagonals(char x, char loc[][BOARDSIZE]);
void test(void);
