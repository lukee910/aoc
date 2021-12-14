#include <stdio.h>

int task1();
void task2(int numlowpoint);

int main()
{
  int numlowpoint = task1();
  task2(numlowpoint);

  return 0;
}

int task1()
{
  FILE *infile = fopen("day9/input.txt", "r");
  int input[102][102];

  for (int i = 0; i < 102; i++)
  {
    input[0][i] = input[i][0] = input[101][i] = input[i][101] = 10;
  }

  for (int i = 1; i < 101; i++)
  {
    for (int j = 1; j < 101; j++)
    {
      char c = getc(infile);
      input[i][j] = c - '0';
    }

    getc(infile);
  }

  int numlowpoint = 0;
  int risklvl = 0;
  for (int i = 1; i < 101; i++)
  {
    for (int j = 1; j < 101; j++)
    {
      int v = input[i][j];
      int left = input[i - 1][j], right = input[i + 1][j], top = input[i][j - 1], bottom = input[i][j + 1];
      if (left > v && right > v && top > v && bottom > v)
      {
        risklvl += v + 1;
        numlowpoint++;
      }
    }
  }

  printf("Found risk level: %d\n", risklvl);
  return numlowpoint;
}

void task2(int numlowpoint)
{
  FILE *infile = fopen("day9/input.txt", "r");
  int input[102][102];

  for (int i = 0; i < 102; i++)
  {
    input[0][i] = input[i][0] = input[101][i] = input[i][101] = 10;
  }

  for (int i = 1; i < 101; i++)
  {
    for (int j = 1; j < 101; j++)
    {
      char c = getc(infile);
      input[i][j] = c - '0';
    }

    getc(infile);
  }

  // Not quite union find
  int ref[102][102];
  int redirects[numlowpoint];
  int basincount = 0;
  int redircount = 0;

  for (int i = 0; i < numlowpoint; i++)
  {
    redirects[i] = -1;
  }

  for (int i = 1; i < 101; i++)
  {
    for (int j = 1; j < 101; j++)
    {
      ref[i][j] = -1;
    }
  }

  for (int i = 1; i < 101; i++)
  {
    for (int j = 1; j < 101; j++)
    {
      int mini = i, minj = j;
      int min = input[i][j];
      if (min >= 9)
      {
        continue;
      }

      int toCheck[4][2] = {
          {i - 1, j},
          {i + 1, j},
          {i, j - 1},
          {i, j + 1}};
      for (int k = 0; k < 4; k++)
      {
        int curr = input[toCheck[k][0]][toCheck[k][1]];
        if (curr < min)
        {
          mini = toCheck[k][0];
          minj = toCheck[k][1];
          min = curr;
        }
      }

      int redir = ref[mini][minj];
      if (redir == -1)
      {
        ref[mini][minj] = redircount++;
        basincount++;
      }
      int oldref = ref[i][j];
      ref[i][j] = ref[mini][minj];

      if (oldref != -1)
      {
        redirects[oldref] = ref[i][j];
        for (int k = 0; k < 0; k++)
        {
          if (redirects[k] == oldref)
          {
            redirects[k] = ref[i][j];
          }
        }
      }
    }
  }

  int basinsize[redircount];
  int max3[3] = {0, 0, 0};

  for (int k = 0; k < redircount; k++)
  {
    basinsize[k] = 0;

    if (redirects[k] == -1)
    {
      basincount++;
      for (int i = 1; i < 101; i++)
      {
        for (int j = 1; j < 101; j++)
        {
          if (ref[i][j] == k || redirects[ref[i][j]] == k)
          {
            basinsize[k]++;
          }
        }
      }

      int v = basinsize[k];
      if (v > max3[0]) {
        int temp = max3[0];
        max3[0] = v;
        v = temp;
      }
      if (v > max3[1]) {
        int temp = max3[1];
        max3[1] = v;
        v = temp;
      }
      if (v > max3[2]) {
        max3[2] = v;
      }
    }
  }

  printf("3 largest basins: %d, %d, %d. Product: %d\n", max3[0], max3[1], max3[2], max3[0] * max3[1] * max3[2]);
}
