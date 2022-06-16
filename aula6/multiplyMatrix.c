#include <stdio.h>
#include <stdlib.h>

#define N 4          // Matrix NxN
#define MAX_VALUE 10 // Max value in rand

void initializeMatrix(int matrix[N][N])
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      matrix[i][j] = rand() % MAX_VALUE;
    }
  }
}

void print(int matrix[N][N])
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      printf("%d\t", matrix[i][j]);
    }
    printf("\n");
  }
}

int main(void)
{
  int matrix1[N][N];
  int matrix2[N][N];
  int result[N][N];

  initializeMatrix(matrix1);
  printf("Matriz 1\n");
  print(matrix1);

  initializeMatrix(matrix2);
  printf("\nMatriz 2\n");
  print(matrix2);

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      result[i][j] = 0;
      for (int k = 0; k < N; k++)
      {
        result[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }

  printf("\nResult\n");
  print(result);

  return 0;
}
