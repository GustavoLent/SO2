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

int multiplyMatrixLineColumn(int line, int column, int matrix1[N][N], int matrix2[N][N])
{
  int result = 0;
  for (int k = 0; k < N; k++)
  {
    result += matrix1[line][k] * matrix2[k][column];
  }

  return result;
}

void iterateOverColumn(int line, int matrix1[N][N], int matrix2[N][N], int result[N][N])
{
  for (int column = 0; column < N; column++)
  {
    result[line][column] = multiplyMatrixLineColumn(line, column, matrix1, matrix2);
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

  for (int line = 0; line < N; line++)
  {
    iterateOverColumn(line, matrix1, matrix2, result);
  }

  printf("\nResult\n");
  print(result);

  return 0;
}
