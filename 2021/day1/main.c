#include <stdio.h>

// Note: Hard coded file paths expect the console to run in the 2021 directory

void task1();
void task2();

int main() {
  task1();
  task2();

  return 0;
}

void task1() {
  FILE *input = fopen("day1/d1input.txt", "r");

  int prev = 0;
  int curr = 0;
  int incr = 0;
  char nextc = '\0';

  do {
    while ((nextc = getc(input)) != '\n' && nextc != EOF) {
      curr = curr * 10 + (nextc - '0');
    }

    if (prev != 0 && curr > prev) {
      incr++;
    }
    prev = curr;
    curr = 0;
  } while (nextc != EOF);

  printf("Increases: %d\n", incr);
}

void task2() {
  FILE *input = fopen("day1/d1input.txt", "r");

  int window1 = 0;
  int window2 = 0;
  int window3 = 0;
  int curr = 0;
  int incr = 0;
  int i = 0;
  char nextc = '\0';

  do {
    while ((nextc = getc(input)) != '\n' && nextc != EOF) {
      curr = curr * 10 + (nextc - '0');
    }

    window2 += curr;
    window3 += curr;

    if (i >= 3 && window1 < window2) {
      incr++;
    }

    // Move windows along
    window1 = window2;
    window2 = window3;
    window3 = curr;
    curr = 0;
    i++;
  } while (nextc != EOF);

  printf("Increases: %d\n", incr);
}
