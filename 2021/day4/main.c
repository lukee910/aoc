#include <stdio.h>

void task1();
void task2();

int main() {
  task1(1);
  task1(0);

  return 0;
}

void task1(int isfirst) {
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

  int boards[100][5][5];
  int remrow[100][5];
  int remcol[100][5];
  int sum[100];
  int boardsrem = 100;
  int completed[100];

  for (int b = 0; b < 100; b++) {
    sum[b] = 0;
    completed[b] = 0;

    for (int i = 0; i < 5; i++) {
      remrow[b][i] = 5;
      remcol[b][i] = 5;

      for (int j = 0; j < 5; j++) {
        int matched = fscanf(input, "%d", &boards[b][i][j]);
        if (!matched) {
          printf("Scan error at boards[%d][%d][%d]\n", b, i, j);
          return;
        }

        sum[b] += boards[b][i][j];

        // read ' ' or '\n'
        getc(input);
      }
    }
  }

  // O(1) kek
  for (int n = 0; n < 100; n++) {
    int num = nums[n];

    // Check for matches
    for (int b = 0; b < 100; b++) {
      if (completed[b]) {
        continue;
      }

      for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
          if (boards[b][i][j] == num) {
            sum[b] -= boards[b][i][j];
            remrow[b][i]--;
            remcol[b][j]--;

            if (remrow[b][i] == 0 || remcol[b][j] == 0) {
              boardsrem--;
              completed[b] = 1;

              if (isfirst || boardsrem == 0) {
                int score = num * sum[b];
                printf("Picked board %d after turn %d with a score of %d\n", b, n, score);
                return;
              }
            }
          }
        }
      }
    }
  }

  printf("Picked no board\n");
}

void task2() {
}
