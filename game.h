#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define BIGSTRING 100
#define BOARDSIZE 3
#define EMPTY ' '
#define GAMEOVER 9

typedef struct {
   char piece;
   char name[BIGSTRING];
} player;

// initialise all positions to ' '
void init_board(char location[][BOARDSIZE]);
// gets input, checks for win, checks for end
bool play_turn(player * plyr, char location[][BOARDSIZE]);
void print_board(char location[][BOARDSIZE]);
bool check_winner(char x, char location[][BOARDSIZE]);
bool check_end(char location[][BOARDSIZE]);
// loops over play turn until finished
void play_game(player * player1, player * player2, char location[][BOARDSIZE]);
void test(void);
