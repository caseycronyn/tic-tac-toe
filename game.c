#include "game.h"

int main(int argc, char *argv[])
{
   // error checking
   if (argc != 3)
   {
      fprintf(stderr, "Proper usage: Player 1 name, Player 2 name\n");
      exit(EXIT_FAILURE);
   }
   if (strlen(argv[1]) > BIGSTRING || strlen(argv[2]) > BIGSTRING)
   {
      fprintf(stderr, "error: player name is malformed\n");
      exit(EXIT_FAILURE);
   }

   // initialisation
   char board[BOARDSIZE][BOARDSIZE];
   init_board(board);

   player player1, player2, cur_player;
   player1.piece = 'X';
   player2.piece = 'O';
   strcpy(player1.name, argv[1]);
   strcpy(player2.name, argv[2]);

   int move[2];
   int * result;
   bool winner = false;
   for (int i = 0; i < GAMEOVER; i++) {
      print_board(board);
      // who's turn
      if (i % 2 == 0) {
         cur_player = player1;
      }
      else {
         cur_player = player2;
      }
      result = get_move(cur_player.name, board, move);
      play_turn(&cur_player, board, result);
      winner = check_winner(cur_player.piece, board);
      if (winner) {
         printf("%s wins!\n\n", cur_player.name);
         return 0;
      }
   }
   printf("Game Over\n");
   return 0;
}

void init_board(char board[][BOARDSIZE])
{
   for (int i = 0; i < BOARDSIZE; i++)
   {
      for (int j = 0; j < BOARDSIZE; j++)
      {
         board[i][j] = EMPTY;
      }
   }
}

bool play_turn(player * plyr, char board[][BOARDSIZE], int * move)
{
   char column = move[0];
   int row = move[1];
   // initialise choice
   board[row][column] = plyr->piece;
   return false;
}

int * get_move(char * name, char board[][BOARDSIZE], int * move)
{
   int row;
   char column;
   // ask for row/ column and verify
   while (true) {
      // ask for choice
      printf("%s's Move: ", name);
      scanf(" %c%d", &column, &row);

      column = tolower(column) - 'a';
      row--;

      if (column >= BOARDSIZE || row >= BOARDSIZE || column < 0 || row < 0) {
         printf("Invalid square. Please pick from a1 to c3");
      }
      if (board[row][column] != EMPTY) {
         printf("Cannot place a piece here, please pick a free position from a1 to c3.\n");
      }
      else {
         move[0] = column;
         move[1] = row;
         return move;
      }
   }
}

bool check_winner(char a, char board[][BOARDSIZE])
{
   if (check_rows_and_cols(a, board) || check_diagonals(a, board)) {
      return true;
   }
   return false;
}

bool check_rows_and_cols(char x, char loc[][BOARDSIZE])
{
   int winr = 0;
   int winc = 0;
   for (int i = 0; i < BOARDSIZE; i++) {
      winr = 0;
      winc = 0;
      for (int j = 0; j < BOARDSIZE; j++) {
         // rows
         if (loc[i][j] == x) {
            winr++;
         }
         if (loc[j][i] == x) {
            winc++;
         }
      }
      if (winr == 3 || winc == 3) {
         return true;
      }
   }
   return false;
}

bool check_diagonals(char x, char loc[][BOARDSIZE])
{
   if ((loc[0][0] == x && loc[1][1] == x && loc[2][2] == x) || (loc[0][2] == x && loc[1][1] == x && loc[2][0] == x)) {
      return true;
   }
   return false;
}

void print_board(char board[][BOARDSIZE])
{
   // format board and assign positions
   printf("    A   B   C \n");
   printf("1   %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
   printf("   ___|___|___\n");
   printf("2   %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
   printf("   ___|___|___\n");
   printf("3   %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
   printf("      |   |      \n\n");
}

void test(void)
{
   return;
}
