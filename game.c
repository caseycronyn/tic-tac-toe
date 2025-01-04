#include "game.h"

int main(int argc, char *argv[])
{
   char * location = init_board();

   // Ensure proper usage
   if (argc != 3)
   {
      printf("Proper usage: Player 1 name, Player 2 name\n");
      exit(EXIT_FAILURE);
   }

   char *player1_s = malloc(sizeof(argv[1]));
   char *player2_s = malloc(sizeof(argv[2]));

   player1_s = argv[1];
   player2_s = argv[2];

   // get First char in name
   char player1_c = player1_s[0];
   char player2_c = player2_s[0];

   printf("Example move: a1\n");

   print_board(location);

   // alternate turns until game over
   do
   {
      bool finished;
      finished = play_turn(player1_c, player1_s, location);
      print_board(location);
      if (finished)
      {
         break;
      }
      finished = play_turn(player2_c, player2_s, location);
      print_board(location);
      if (finished)
      {
         break;
      }
   }
   while (check_end(location) == false);

   // check if game finished
   printf("Game Over\n");
}

char * init_board(void)
{
   // location array
   char *location = malloc(9 * sizeof(char));

   // Initialise all positions to ' '
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         location[(i * 3) + j] = ' ';
      }
   }
   return location;
}

bool play_turn(char player_c, char *player_s, char *location)
{
   int row;
   char column;
   // ask for row/ column and verify
   do
   {
      // ask for choice
      printf("%s's Move: ", player_s);
      scanf(" %c%i", &column, &row);

      // 0 index
      column = tolower(column) - 'a';
      row--;

      if (location[(row * 3) + column] != ' ')
      {
         printf("Position unavailable, pick another. (Move format example where square is empty: a1)\n");
      }
   }
   while (location[(row * 3) + column] != ' ');

   // initialise choice
   location[(row * 3) + column] = player_c;

   // check for win and print winner
   if (check_winner(player_c, location))
   {
      printf("%s wins!\n\n", player_s);
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

void print_board(char *location)
{
   // format board and assign positions
   printf("    A   B   C \n");
   printf("1   %c | %c | %c \n", location[0], location[1], location[2]);
   printf("   ___|___|___\n");
   printf("2   %c | %c | %c \n", location[3], location[4], location[5]);
   printf("   ___|___|___\n");
   printf("3   %c | %c | %c \n", location[6], location[7], location[8]);
   printf("      |   |      \n\n");
}

bool check_winner(char a, char *location)
{
   // check rows and columns
   int win_r;
   int win_c;
   for (int x = 0; x < 3; x++)
   {
      win_r = 0;
      win_c = 0;
      for (int y = 0; y < 3; y++)
      {
         // check rows
         if (location[(y * 3) + x] == a)
         {
            win_r++;
         }
         // check columns
         if (location[(x * 3) + y] == a)
         {
            win_c++;
         }
      }
      if (win_r == 3 || win_c == 3)
      {
         return true;
      }
   }
   // check diagonals
   if ((location[0] == a && location[4] == a && location[8] == a) || (location[2] == a && location[4] == a && location[6] == a))
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool check_end(char *location)
{
   char end = 0;
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         if (location[(i * 3) + j] == ' ')
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
