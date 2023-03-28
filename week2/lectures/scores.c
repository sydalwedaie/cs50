#include <cs50.h>
#include <stdio.h>

const int N = 4;
float average(int array[]);

int main(void)
{
  int scores[N];
  for (int i = 0; i < N; i++)
  {
    scores[i] = get_int("Score: ");
  }

  printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / (float) 3);
}

float average(int array[])
{
  int total = 0;
  for (int i = 0; i < N; i++)
  {
    total += array[i];
  }
  return total / (float) N;
}