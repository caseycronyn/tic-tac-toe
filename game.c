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

   char location[BOARDSIZE][BOARDSIZE];
   init_board(location);
   // names
   char * player1_s = argv[1];
   char * player2_s = argv[2];

   player player1, player2;
   player1.piece = 'X';
   player2.piece = 'O';
   strcpy(player1.name, argv[1]);
   strcpy(player2.name, argv[2]);

   play_game(&player1, &player2, location);
   // check if game finished
   printf("Game Over\n");
}

void play_game(player * player1, player * player2, char location[][BOARDSIZE])
{
   bool end = false;
   for (int i = 0; i < GAMEOVER; i++) {
      print_board(location);
      // who's turn
      if (i % 2 == 0) {
         end = play_turn(player1, location);
      }
      else {
         end = play_turn(player2, location);
      }
      // done
      if (end || check_end(location)) {
         i = GAMEOVER;
      }
   }
}

void init_board(char location[][BOARDSIZE])
{
   for (int i = 0; i < BOARDSIZE; i++)
   {
      for (int j = 0; j < BOARDSIZE; j++)
      {
         location[i][j] = EMPTY;
      }
   }
}

bool play_turn(player * plyr, char location[][BOARDSIZE])
{
   int row;
   char column;
   // get input
   // ask for row/ column and verify
   do
   {
      // ask for choice
      printf("%s's Move: ", plyr->name);
      scanf(" %c%i", &column, &row);

      // 0 index
      column = tolower(column) - 'a';
      row--;

      if (location[row][column] != EMPTY)
      {
         printf("Position unavailable, pick another. (Move format example where square is empty: a1)\n");
      }
   }
   while (location[row][column] != ' ');

   // initialise choice
   location[row][column] = plyr->piece;

   // check for win and print winner
   if (check_winner(plyr->piece, location))
   {
      printf("%s wins!\n\n", plyr->name);
      return true;
   }

   // check for end
   if (check_end(location))
   {
      printf("Tie\n");
      return true;
   }

   return false;
}

void print_board(char location[][BOARDSIZE])
{
   // format board and assign positions
   printf("    A   B   C \n");
   printf("1   %c | %c | %c \n", location[0][0], location[0][1], location[0][2]);
   printf("   ___|___|___\n");
   printf("2   %c | %c | %c \n", location[1][0], location[1][1], location[1][2]);
   printf("   ___|___|___\n");
   printf("3   %c | %c | %c \n", location[2][0], location[2][1], location[2][2]);
   printf("      |   |      \n\n");
}

bool check_winner(char a, char location[][BOARDSIZE])
{
   // check rows and columns
   int win_r;
   int win_c;
   for (int x = 0; x < BOARDSIZE; x++)
   {
      win_r = 0;
      win_c = 0;
      for (int y = 0; y < BOARDSIZE; y++)
      {
         // check rows
         if (location[y][x] == a)
         {
            win_r++;
         }
         // check columns
         if (location[x][y] == a)
         {
            win_c++;
         }
      }
      if (win_r == BOARDSIZE || win_c == BOARDSIZE)
      {
         return true;
      }
   }
   // check diagonals
   if ((location[0][0] == a && location[1][1] == a && location[2][2] == a) || (location[0][2] == a && location[1][1] == a && location[2][0] == a))
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool check_end(char location[][BOARDSIZE])
{
   char end = 0;
   for (int i = 0; i < BOARDSIZE; i++)
   {
      for (int j = 0; j < BOARDSIZE; j++)
      {
         if (location[i][j] == ' ')
         {
            return false;
         }
      }
   }
   return true;
}

void test(void)
{
   return;
}
