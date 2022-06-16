#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define N 100        // Matrix NxN
#define MAX_VALUE 10 // Max value in rand

struct initializeRandomMatrixParameters
{
  intptr_t matrix[N][N];
};

void *initializeRandomMatrix(void *parameters)
{
  struct initializeRandomMatrixParameters *p = (struct initializeRandomMatrixParameters *)parameters;

  for (intptr_t i = 0; i < N; i++)
  {
    for (intptr_t j = 0; j < N; j++)
    {
      p->matrix[i][j] = rand() % MAX_VALUE;
    }
  }
}

void initializeMatrixFromOther(intptr_t matrix1[N][N], intptr_t matrix2[N][N])
{
  for (intptr_t i = 0; i < N; i++)
  {
    for (intptr_t j = 0; j < N; j++)
    {
      matrix1[i][j] = matrix2[i][j];
    }
  }
}

void print(intptr_t matrix[N][N])
{
  for (intptr_t i = 0; i < N; i++)
  {
    for (intptr_t j = 0; j < N; j++)
    {
      printf("%ld\t", matrix[i][j]);
    }
    printf("\n");
  }
}

void writeMatrixIntoFile(intptr_t matrix[N][N], FILE *fptr)
{
  for (intptr_t i = 0; i < N; i++)
  {
    for (intptr_t j = 0; j < N; j++)
    {
      fprintf(fptr, "%ld ", matrix[i][j]);
    }

    fprintf(fptr, "\n");
  }
}

struct multiplyMatrixLineColumnParameters
{
  intptr_t line;
  intptr_t column;
  intptr_t matrix1[N][N];
  intptr_t matrix2[N][N];
};

void *multiplyMatrixLineColumn(void *parameters)
{
  intptr_t result = 0;
  struct multiplyMatrixLineColumnParameters *p = (struct multiplyMatrixLineColumnParameters *)parameters;

  for (intptr_t k = 0; k < N; k++)
  {
    result += p->matrix1[p->line][k] * p->matrix2[k][p->column];
  }

  return (void *)result;
}

struct iterateOverColumnParameters
{
  intptr_t line;
  intptr_t matrix1[N][N];
  intptr_t matrix2[N][N];
  intptr_t result[N][N];
};

void *iterateOverColumn(void *parameters)
{
  struct iterateOverColumnParameters *p = (struct iterateOverColumnParameters *)parameters;

  for (intptr_t column = 0; column < N; column++)
  {
    struct multiplyMatrixLineColumnParameters params;
    params.line = p->line;
    params.column = column;

    initializeMatrixFromOther(params.matrix1, p->matrix1);
    initializeMatrixFromOther(params.matrix2, p->matrix2);

    pthread_t thread;
    intptr_t value;

    pthread_create(&thread, NULL, &multiplyMatrixLineColumn, &params);
    pthread_join(thread, (void *)&value);

    p->result[p->line][column] = value;
  }
}

intptr_t main(void)
{

  struct initializeRandomMatrixParameters randomMatrix1;
  pthread_t matrix1Thread;
  pthread_create(&matrix1Thread, NULL, &initializeRandomMatrix, &randomMatrix1);

  pthread_t matrix2Thread;
  struct initializeRandomMatrixParameters randomMatrix2;
  pthread_create(&matrix2Thread, NULL, &initializeRandomMatrix, &randomMatrix2);

  pthread_join(matrix1Thread, NULL);
  pthread_join(matrix2Thread, NULL);

  printf("As duas matrizes foram criadas randomicamente\n");

  intptr_t result[N][N];

  for (intptr_t line = 0; line < N; line++)
  {
    printf("Calculando para a linha \"%ld\"\n", line);

    struct iterateOverColumnParameters params;
    params.line = line;

    initializeMatrixFromOther(params.matrix1, randomMatrix1.matrix);
    initializeMatrixFromOther(params.matrix2, randomMatrix2.matrix);
    initializeMatrixFromOther(params.result, result);

    pthread_t thread;

    pthread_create(&thread, NULL, &iterateOverColumn, &params);
    pthread_join(thread, NULL);

    initializeMatrixFromOther(result, params.result);
  }

  printf("A matriz resultante foi calculada\n");

  FILE *fptr;
  fptr = fopen("./resultado.txt", "w");

  if (fptr == NULL)
  {
    printf("Error!");
    exit(1);
  }

  fprintf(fptr, "Matriz 1\n");
  writeMatrixIntoFile(randomMatrix1.matrix, fptr);

  fprintf(fptr, "\nMatriz 2\n");
  writeMatrixIntoFile(randomMatrix2.matrix, fptr);

  fprintf(fptr, "\nResultado\n");
  writeMatrixIntoFile(result, fptr);

  fclose(fptr);

  printf("O resultado foi escrito no arquivo!\n");

  return 0;
}
