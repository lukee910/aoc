#include <stdio.h>

void task1();
void task2();

int main()
{
  task1();
  task2();

  return 0;
}

void task1()
{
  FILE *input = fopen("day7/input.txt", "r");

  int rave[1000];
  int maxpos = 0;
  for (int i = 0; i < 1000; i++)
  {
    int pos;
    int matched = fscanf(input, "%d", &pos);
    if (matched != 1)
    {
      printf("Error on reading pos %d\n", i);
    }
    getc(input);

    if (pos > maxpos)
    {
      maxpos = pos;
    }

    for (int j = 0; j < i; j++)
    {
      if (rave[j] > pos)
      {
        int temp = rave[j];
        rave[j] = pos;
        pos = temp;
      }
    }
    rave[i] = pos;
  }

  printf("Read crabs, max is %d\n", maxpos);

  int selcost = __INT_MAX__;
  int selpos = 0;

  // This can be done with binary search or calculating adjacent costs more smartly,
  // but I am lazy, just try everything :3
  for (int i = 0; i < maxpos; i++)
  {
    int cost = 0;
    for (int j = 0; j < 1000; j++)
    {
      if (rave[j] < i)
      {
        cost += (i - rave[j]);
      }
      else
      {
        cost += (rave[j] - i);
      }
    }

    if (cost < selcost)
    {
      selcost = cost;
      selpos = i;

      // printf("New best selection: pos %d with cost %d\n", selpos, selcost);
    }
  }

  printf("Selected position %d with cost %d\n", selpos, selcost);
}

void task2() {
  FILE *input = fopen("day7/input.txt", "r");

  int rave[1000];
  int maxpos = 0;
  for (int i = 0; i < 1000; i++)
  {
    int matched = fscanf(input, "%d", &rave[i]);
    if (matched != 1)
    {
      printf("Error on reading pos %d\n", i);
    }
    getc(input);

    if (rave[i] > maxpos)
    {
      maxpos = rave[i];
    }
  }

  printf("Read crabs, max is %d\n", maxpos);

  int selcost = __INT_MAX__;
  int selpos = 0;

  for (int i = 0; i < maxpos; i++)
  {
    int cost = 0;
    for (int j = 0; j < 1000; j++)
    {
      int x;
      if (rave[j] < i)
      {
        x = (i - rave[j]);
      }
      else
      {
        x = (rave[j] - i);
      }
      cost += ((x + 1) * x) / 2;
    }

    if (cost < selcost)
    {
      selcost = cost;
      selpos = i;

      // printf("New best selection: pos %d with cost %d\n", selpos, selcost);
    }
  }

  printf("Selected position %d with cost %d\n", selpos, selcost);
}
