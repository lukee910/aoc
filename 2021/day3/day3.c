#include <stdio.h>
#include <stdlib.h>

// Input dimensions 1000x12 hard coded
#define NUM_MEASURES 1000
#define WIDTH_MEASURES 12

void task1();
void task2();
int findPattern(int pattern, int *in);
void printBinary(int value);

int main() {
  task1();
  task2();

  return 0;
}

void task1() {
  FILE *input = fopen("day3/input.txt", "r");

  int in[NUM_MEASURES];

  for (int j = 0; j < NUM_MEASURES; j++) {
    // Init value in array
    in[j] = 0;
    for (int i = 0; i < WIDTH_MEASURES; i++) {
      in[j] = (in[j]<<1) | (getc(input) - '0');
    }

    // if (j < 2) {
    //   printBinary(in[j]);
    //   printf("\n");
    // }

    // Read newline/EOF
    getc(input);
  }

  int gamma = 0;
  int eps = 0;
  for (int i = 0; i < WIDTH_MEASURES; i++) {
    int num1 = 0;
    int mask = 1<<(WIDTH_MEASURES - i - 1);
    for (int j = 0; j < NUM_MEASURES; j++) {
      if (in[j] & mask) {
        num1++;
      }
    }

    if (num1 > NUM_MEASURES / 2) {
      gamma = gamma | mask;
    } else {
      eps = eps | mask;
    }
  }

  printf("Gamma: %d / %X, Eps: %d / %X, Product: %d\n", gamma, gamma, eps, eps, gamma * eps);
}

void task2() {
  FILE *input = fopen("day3/input.txt", "r");

  int in[NUM_MEASURES];

  for (int j = 0; j < NUM_MEASURES; j++) {
    // Init value in array
    in[j] = 0;
    for (int i = 0; i < WIDTH_MEASURES; i++) {
      in[j] = (in[j]<<1) | (getc(input) - '0');
    }

    // Read newline/EOF
    getc(input);
  }

  int gamma = 0;
  int eps = 0;
  for (int i = 0; i < WIDTH_MEASURES; i++) {
    int num1 = 0;
    int mask = 1<<(WIDTH_MEASURES - i - 1);
    for (int j = 0; j < NUM_MEASURES; j++) {
      if (in[j] & mask) {
        num1++;
      }
    }

    if (num1 > NUM_MEASURES / 2) {
      gamma = gamma | mask;
    } else {
      eps = eps | mask;
    }
  }

  // Gamma is the expected bit pattern for O2, eps is the expected bit pattern for CO2  
  int o2 = findPattern(gamma, in);
  int co2 = findPattern(eps, in);

  printf("O2: %d, CO2: %d, Product: %d\n", o2, co2, o2 * co2);
}

int findPattern(int pattern, int *in) {
  int count = NUM_MEASURES;
  int col = WIDTH_MEASURES - 1;

  int nextrow = 0;
  int *curr = in;
  int *next = malloc(count * sizeof(int));
  while (count > 1) {
    for (int i = 0; i < count; i++) {
      if (((curr[i]>>col) & 1) == ((pattern>>col) & 1)) {
        next[nextrow++] = curr[i];
      }
    }

    if (curr != in) {
      free(curr);
    }
    curr = next;

    count = nextrow - 1;
    col--;
  }

  return next[0];
}

void printBinary(int value) {
  int sz = sizeof(int) * 8;
  int b[sz];
  for (int i = sz - 1; i >= 0; i--) {
    b[sz - i - 1] = (value>>i) & 1;
  }
  for (int i = 0; i < sz; i++) {
    printf("%X", b[i]);
  }
}
