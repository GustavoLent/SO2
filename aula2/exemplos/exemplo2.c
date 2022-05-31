#include <stdio.h>

int main (int argc, char* argv[])
{
  printf ("O nome do programa é '%s'.\n", argv[0]);
  printf ("Este programa foi chamado com %d argumentos.\n", argc - 1);

  /* Algum argumento de linha de comando foi especificado?  */
  if (argc > 1) {
    /* Sim, imprima-os.  */
    int i;
    printf ("Os argumentos são:\n");
    for (i = 1; i < argc; ++i)
      printf ("  %s\n", argv[i]);
  }

  return 0;
}