#include <stdio.h>

void task1();
void task2();

int main() {
  task1();
  task2();

  return 0;
}

void task1() {
  FILE *input = fopen("day4/input.txt", "r");

  int nums[100];
  for (int i = 0; i < 100; i++) {
    nums[i] = 0;
  }

  // Read drawn numbers
  char nextc;
  int numc = 0;
  while ((nextc = getc(input)) != '\n') {
    if (nextc == ',') {
      numc++;
    } else {
      nums[numc] = nums[numc] * 10 + (nextc - '0');
    }
  }

  // printf("Done reading input: ");
  // for (int i = 0; i < 100; i++) {
  //   printf("%d, ", nums[i]);
  // }
  // printf("\n");

  // The board that is drawn first 
  int first = 0;
  // The turn in which the first board is completed
  int firstturn = 100;
  // The score of the first
  int firstscore = 0;

  // Calculate board win time and values
  int numboard = 0;
  while (getc(input) != EOF) {
    printf("Calculating board %d\n", numboard);

    int board[5][5];
    // int marked[5][5];
    int colrem[5];
    int rowrem[5];
    int sumunmarked = 0;

    // Clear arrays
    for (int i = 0; i < 5; i++) {
      // for (int j = 0; j < 5; j++) {
      //   marked[i][j] = 0;
      // }
      colrem[i] = 5;
      rowrem[i] = 5;
    }

    // Line i
    // printf("    Reading board:\n");
    for (int i = 0; i < 5; i++) {
      // Entry j on line i
      // printf("    ");
      for (int j = 0; j < 5; j++) {
        int c1 = getc(input);
        // printf("[%d=%c, ", c1, c1);
        if (c1 == ' ') {
          c1 = '\0';
        } else {
          c1 -= '0';
        }

        int c2 = getc(input);
        // printf("%d=%c], ", c2, c2);
        c2 -= '0';

        board[i][j] = (c1 * 10) + c2;
        sumunmarked += board[i][j];
        // printf("%d, ", board[i][j]);

        // printf("%d, ", board[i][j]);
        // printf("[%d, %d]", c1, c2);

        // Read ' ' or '\n'
        getc(input);
      }
      // printf("\n");
    }

    // Check board
    int turn = 0;
    int complete = 0;
    while (turn <= firstturn) {
      int num = nums[turn];
      int marked = 0;

      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
          if (board[i][j] == num) {
            // printf("    Marked %d in turn %d\n", num, turn);

            marked = 1;
            sumunmarked -= num;
            if (--rowrem[i] == 0 || --colrem[j] == 0) {
              printf("    Completed in turn %d\n", turn);
              complete = 1;
            }
            break;
          }
        }
        if (marked) {
          break;
        }
      }

      if (complete) {
        break;
      }

      turn++;
    }

    // Calculate score
    if (complete) {
      int score = turn * sumunmarked;
      if (turn < firstturn || score > firstscore) {
        first = numboard;
        firstscore = score;
        firstturn = turn;
      } else {
        printf("Board not taken!\n");
      }
    }

    if (numboard == 68) {
      for (int i = 0; i <= turn; i++) {
        printf("%d, ", nums[i]);
      }
      printf("\n");
      for(int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
          printf("%d, ", board[i][j]);
        }
        printf("\n");
      }
    }

    numboard++;
  }

  printf("Picked board %d after turn %d with a score of %d\n", first, firstturn, firstscore);
}

void task2() {
}
