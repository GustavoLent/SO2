#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdint.h>

#define amountOfColuns 5
#define amountOfLines 4

struct lineSumParameters
{
  int arr[amountOfColuns];
  int size;
  int id;
};

void *lineSum(void *parameters)
{
  intptr_t sum = 0;
  struct lineSumParameters *p = (struct lineSumParameters *)parameters;

  printf("Linha %d) ", p->id);

  for (int t = 0; t < p->size; t++)
  {
    printf("%d ", p->arr[t]);

    if (t < p->size - 1)
    {
      printf("+ ");
    }
    else
    {
      printf("= ");
    }

    sum = sum + p->arr[t];
  }

  printf("%ld\n", sum);
  return (void *)sum;
}

int main()
{
  int matrix[amountOfLines][amountOfColuns] = {
      1, 2, 3, 4, 5,
      6, 7, 8, 9, 10,
      11, 12, 13, 14, 15,
      16, 17, 18, 19, 20};

  intptr_t linesSum = 0;
  intptr_t sumVal = 0;

  for (int i = 0; i < amountOfLines; i++)
  {
    pthread_t thread;
    struct lineSumParameters args;

    for (int j = 0; j < amountOfColuns; j++)
    {
      args.arr[j] = matrix[i][j];
    }

    args.id = i;
    args.size = amountOfColuns;

    pthread_create(&thread, NULL, &lineSum, &args);
    pthread_join(thread, (void *)&sumVal);
    linesSum = linesSum + sumVal;
  }

  printf("Total: %ld\n", linesSum);
  return 0;
}