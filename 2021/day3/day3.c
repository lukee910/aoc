#include <stdio.h>
#include <stdlib.h>

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

int **task1(int print);
void task2();
int findPattern(int pattern, int *in);
void printBinary(int value);

int main()
{
  task1(1);
  task2();

  return 0;
}

int **task1(int print)
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

  int *values = malloc(2 * sizeof(int));
  values[0] = gamma;
  values[1] = eps;

  int **ret = malloc(2 * sizeof(int));
  ret[0] = values;
  ret[1] = in;

  return ret;
}

void task2()
{
  int **t1res = task1(0);

  int gamma = t1res[0][0];
  int eps = t1res[0][1];
  int *in = t1res[1];

  // Gamma is the expected bit pattern for O2, eps is the expected bit pattern for CO2
  int o2 = findPattern(gamma, in);
  int co2 = findPattern(eps, in);

  printf("O2: %d, CO2: %d, Product: %d\n", o2, co2, o2 * co2);
}

int findPattern(int pattern, int *in)
{
  int count = NUM_MEASURES;
  int col = WIDTH_MEASURES - 1;

#ifdef DEBUG
  printf("Finding pattern: ");
  printBinary(pattern);
  printf("\n");
#endif

  int nextrow = 0;
  int curr[NUM_MEASURES];

  for (int i = 0; i < NUM_MEASURES; i++)
  {
    curr[i] = in[i];
  }

  while (count > 1)
  {
    DPRINT("-- Iteration start\n");
    DPRINT("col  : %d\n", col);
    DPRINT("count: %d\n", count);
    // DPRINT("curr : %p\n", curr);

    for (int i = 0; i < count; i++)
    {
      if (((curr[i] >> col) & 1) == ((pattern >> col) & 1))
      {
        curr[nextrow++] = curr[i];

        if (count < 9)
        {
          DPRINT("Entry added: %X, index %d to %d\n", curr[i], i, nextrow - 1);
        }
      }
    }

    count = nextrow - 1;
    nextrow = 0;
    col--;
  }

  DPRINT("Pattern %X matched with %X\n", pattern, curr[0]);

  return curr[0];
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
