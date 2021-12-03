#include <stdio.h>

void task1();
void task2();

int main() {
  task1();
  task2();

  return 0;
}

void task1() {
  FILE *input = fopen("day2/d2input.txt", "r");

  int depth = 0;
  int fwd = 0;
  char nextc = '\0';
  // Get direction by its first char
  char curr = '\0';
  int curramount = 0;

  do {
    nextc = getc(input);
    // Check EOF for newline before EOF
    if (nextc == EOF) {
      break;
    }

    curr = nextc;

    while ((nextc = getc(input)) != ' ');

    while ((nextc = getc(input)) != '\n' && nextc != EOF) {
      curramount = curramount * 10 + (nextc - '0');
    }

    switch (curr)
    {
    case 'f':
      fwd += curramount;
      break;
    case 'd':
      depth += curramount;
      break;
    case 'u':
      depth -= curramount;
      break;
    }

    curramount = 0;
  } while (nextc != EOF);

  printf("Depth: %d, Forward pos: %d, Product: %d\n", depth, fwd, depth * fwd);
}

void task2() {}
