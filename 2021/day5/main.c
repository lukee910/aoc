#include <stdio.h>

void task1();
void task2();

int main() {
  task1();
  task2();

  return 0;
}

void task1() {
  FILE *input = fopen("day5/input.txt", "r");

  int lines[500][2][2];
  int p[1000][1000];

  int dangerous = 0;

  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      p[i][j] = 0;
    }
  }

  for (int l = 0; l < 500; l++) {
    int err = fscanf(input, "%d,%d -> %d,%d\n", &lines[l][0][0], &lines[l][0][1], &lines[l][1][0], &lines[l][1][1]);
    if (err) {
      printf("Error on reading line %d\n", l);
      return;
    }

    int x1 = lines[l][0][0], x2 = lines[l][0][1], y1 = lines[l][1][0], y2 = lines[l][1][1];

    if (x1 == x2) {
      if (y1 > y2) {
        int temp = y1;
        y1 = y2;
        y2 = temp;
      }

      for (int i = y1; i <= y2; i++) {
        p[x1][i]++;
        // Count as dangerous on the first time increasing above 2, only counted once therefore
        if (p[x1][i] == 2) {
          dangerous++;
        }
      }
    }

    if (y1 == y2) {
      if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;
      }

      for (int i = x1; i <= x2; i++) {
        p[i][y1]++;
        // Count as dangerous on the first time increasing above 2, only counted once therefore
        if (p[i][y1] == 2) {
          dangerous++;
        }
      }
    }
  }

  printf("Dangerous points: %d\n", dangerous);
}

void task2() {}
