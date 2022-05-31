#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

/* O nome deste programa.  */
const char* program_name;

/* Imprime as informações de uso do programa para o STREAM (tipicamente
   stdout ou stderr), e sai do programa com o código EXIT_CODE.  Não retorna.  */

void print_usage (FILE* stream, int exit_code)
{
  fprintf (stream, "Uso:  %s opções [ arquivoentrada ... ]\n", program_name);
  fprintf (stream,
           "  -h  --help                  Mostra estas informações de uso.\n"
           "  -o  --output filename       Escreve saída para um arquivo.\n"
           "  -v  --verbose               Imprime mensagens verbosas.\n");
  exit (exit_code);
}

/* Ponto de entrada do programa principal. ARGC contém o números de elementos na lista de argumentos; ARGV é um conjunto de ponteiros para eles.  */

int main (int argc, char* argv[])
{
  int next_option;

  /* Uma string listando letras de opções curtas válidas.  */
  const char* const short_options = "ho:v";
  /* Um conjunto descrevendo opções longas válidas.  */
  const struct option long_options[] = {
    { "help",     0, NULL, 'h' },
    { "output",   1, NULL, 'o' },
    { "verbose",  0, NULL, 'v' },
    { NULL,       0, NULL, 0   }   /* Requerido no final do conjunto.  */
  };

/* O nome do arquivo que receberá a saída do programa , ou NULL para a saída padrão.  */
  const char* output_filename = NULL;
  /* Mostrar ou não mensagens prolixas.  */
  int verbose = 0;

  /* Lembrar o nome do programa, para incorporá-lo nas mensagens.
     O nome está armazenado em argv[0].  */
  program_name = argv[0];

  do 
  {
    next_option = getopt_long (argc, argv, short_options,
                               long_options, NULL);
    switch (next_option)
    {
    case 'h':   /* -h ou --help */
      /* Usuário requisitou informações de uso. Imprima para a saída padrão, e então saia com o código de saída zero (terminação normal).  */
      print_usage (stdout, 0);

    case 'o':   /* -o ou --output */
      /* Esta opção tem um argumento, o nome do arquivo.  */
      output_filename = optarg;
      break;

    case 'v':   /* -v ou --verbose */
      verbose = 1;
      break;  

    case '?':   /* O usuário especificou uma opção inválida.  */
          /* Imprima informação de uso do erro padrão, e saia com o código de saída um (indicando terminação anormal).  */
          print_usage (stderr, 1);

    case -1:    /* Fim das opções.  */
      break;

    default:    /* Algo mais: inesperado.  */
      abort ();
    }
  }while (next_option != -1);

      /* Fim das opções.  OPTIND aponta para o primeiro argumento que não é opção. Para efeito de demonstração, imprima-os se a opção verbose foi especificada.  */
      if (verbose) {

        int i;
        for (i = optind; i < argc; ++i) 
          printf ("Argumentos: %s\n", argv[i]);
      }

      /* O programa principal vai aqui.  */

      return 0;
    }