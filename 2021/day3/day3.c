#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

#ifdef DEBUG
#define DPRINT(...) printf(__VA_ARGS__)
#else
#define DPRINT(...) \
  do                \
  {                 \
  } while (0);
#endif

// Input dimensions 1000x12 hard coded
#define NUM_MEASURES 1000
#define WIDTH_MEASURES 12

void task1(int print);
void task2();
int findval(int in[NUM_MEASURES][WIDTH_MEASURES], int takemaj);
void printBinary(int value);

int main()
{
  task1(1);
  task2();

  return 0;
}

void task1(int print)
{
  FILE *input = fopen("day3/input.txt", "r");

  int *in = malloc(NUM_MEASURES * sizeof(int));

  for (int j = 0; j < NUM_MEASURES; j++)
  {
    // Init value in array
    in[j] = 0;
    for (int i = 0; i < WIDTH_MEASURES; i++)
    {
      in[j] = (in[j] << 1) | (getc(input) - '0');
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
  for (int i = 0; i < WIDTH_MEASURES; i++)
  {
    int num1 = 0;
    int mask = 1 << (WIDTH_MEASURES - i - 1);
    for (int j = 0; j < NUM_MEASURES; j++)
    {
      if (in[j] & mask)
      {
        num1++;
      }
    }

    if (num1 > NUM_MEASURES / 2)
    {
      gamma = gamma | mask;
    }
    else
    {
      eps = eps | mask;
    }
  }

  if (print)
  {
    printf("Gamma: %d / ", gamma);
    printBinary(gamma);
    printf(", Eps: %d / ", eps);
    printBinary(eps);
    printf(", Product: %d\n", gamma * eps);
  }
}

void task2()
{
  FILE *input = fopen("day3/input.txt", "r");

  // Screw optimization in an int like in task 1
  int in[NUM_MEASURES][WIDTH_MEASURES];

  for (int i = 0; i < NUM_MEASURES; i++)
  {
    // Init value in array
    for (int j = 0; j < WIDTH_MEASURES; j++)
    {
      in[i][j] = getc(input) - '0';
    }

    // Read newline/EOF
    getc(input);
  }

  int o2 = findval(in, 1);
  int co2 = findval(in, 0);

  printf("o2: %d, co2: %d, product: %d\n", o2, co2, o2 * co2);
}

int findval(int in[NUM_MEASURES][WIDTH_MEASURES], int takemaj)
{
  int values[NUM_MEASURES][WIDTH_MEASURES];
  memcpy(values, in, NUM_MEASURES * WIDTH_MEASURES * sizeof(int));

  int count = NUM_MEASURES;
  int col = WIDTH_MEASURES - 1;
  int next = 0;
  while (count > 1)
  {
    DPRINT("-- start iteration --\n");
    int num1 = 0;
    for (int i = 0; i < count; i++)
    {
      if (values[i][col])
      {
        num1++;
      }
    }
    int take1 = num1 >= (count / 2);
    if (!takemaj)
    {
      take1 = !take1;
    }
    DPRINT("count: %d, num1: %d, take1: %d\n", count, num1, take1);

    for (int i = 0; i < count; i++)
    {
      if (values[i][col] == take1)
      {
        memcpy(values[next++], values[i], WIDTH_MEASURES * sizeof(int));
      }
    }

    count = next - 1;
    next = 0;
  }
  int result = 0;
  for (int i = 0; i < WIDTH_MEASURES; i++)
  {
    result = (result << 1) | values[0][i];
  }

  return result;
}

void printBinary(int value)
{
  int sz = WIDTH_MEASURES;
  int b[sz];
  for (int i = sz - 1; i >= 0; i--)
  {
    b[sz - i - 1] = (value >> i) & 1;
  }
  for (int i = 0; i < sz; i++)
  {
    printf("%X", b[i]);
  }
}
