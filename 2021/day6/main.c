#include <stdio.h>
#include <stdlib.h>

void task1();
void task2();

struct Feeeeesh
{
  int countdown;
  struct Feeeeesh *next;
};
#define Feeeeesh struct Feeeeesh

int main()
{
  task1();
  task2();

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
  // Feeeeesh *curr = list;
  // while (curr != NULL)
  // {
  //   printf("%d, ", curr->countdown);
  //   curr = curr->next;
  // }
  // printf("\n");

  // Simulate 80 days
  for (int i = 0; i < 80; i++)
  {
    printf("Simulating day %d\n", i);

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
    printf("\n");
  }

  printf("Num of feeeeeshes after 80 days: %d\n", size);
}

void task2() {}
