#include <stdio.h>
#include <stdlib.h>

void task1();
void task2(int numdays);

struct Feeeeesh
{
  int countdown;
  struct Feeeeesh *next;
};
#define Feeeeesh struct Feeeeesh

int main()
{
  task1();
  task2(80);
  task2(256);

  return 0;
}

void task1()
{
  FILE *input = fopen("day6/input.txt", "r");

  // Init list and first element
  int size = 1;
  Feeeeesh *list = malloc(sizeof(Feeeeesh));
  int matched = fscanf(input, "%d,", &list->countdown);
  if (matched != 1)
  {
    printf("Could not match first element\n");
  }

  // Fill rest of list
  Feeeeesh *prev = list;
  do
  {
    size++;
    Feeeeesh *curr = malloc(sizeof(Feeeeesh));
    prev->next = curr;
    matched = fscanf(input, "%d", &curr->countdown);
    if (matched != 1)
    {
      printf("Could not match first element\n");
    }

    prev = curr;
  } while (getc(input) != EOF);

  // Ensure end pointer NULL
  prev->next = NULL;

  printf("Found %d feeeeeshes\n", size);

  // Simulate 80 days
  for (int i = 0; i < 80; i++)
  {
    Feeeeesh *curr = list;
    while (curr != NULL)
    {
      curr->countdown--;
      if (curr->countdown == -1)
      {
        size++;
        curr->countdown = 6;
        Feeeeesh *next = malloc(sizeof(Feeeeesh));
        next->countdown = 8;
        next->next = curr->next;
        curr->next = next;
        curr = next;
      }

      curr = curr->next;
    }
  }

  printf("Num of feeeeeshes after 80 days: %d\n", size);
}

void task2(int numdays)
{
  FILE *input = fopen("day6/input.txt", "r");

  // Init list and first element
  unsigned long count = 0;
  unsigned long ttr[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  do
  {
    int value;
    int matched = fscanf(input, "%d", &value);
    if (matched != 1)
    {
      printf("Error on scan\n");
      return;
    }
    ttr[value]++;
    count++;
  } while (getc(input) != EOF);

  printf("Found %lu feeeeeshes\n", count);

  // Simulate numfeeeeeshes days
  for (int i = 0; i < numdays; i++)
  {
    unsigned long repro = ttr[0];
    for (int i = 1; i < 9; i++)
    {
      ttr[i - 1] = ttr[i];
      ttr[i] = 0;
    }

    ttr[6] += repro;
    ttr[8] += repro;
    count += repro;
  }

  printf("Num of feeeeeshes after %d days: %lu\n", numdays, count);
}
