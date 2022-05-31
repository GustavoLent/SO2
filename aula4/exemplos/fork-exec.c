#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* Gera um processo filho executando um novo programa.  
   PROGRAM é o nome do programa a ser executado; ele
   será buscado no path. ARG_LIST é uma lista terminada
   em NULL de strings de caracteres a serem passados
   como a lista de argumentos do programa. Retorna o id
   do processo gerado.  */

int spawn (char* program, char** arg_list)
{
  pid_t child_pid;

  /* Duplicar este processo.  */
  child_pid = fork ();
  if (child_pid != 0)
    /* Este é o processo pai.  */
    return child_pid;
  else {
    /* Agora execute PROGRAM,  buscando-o no path.  */
    execvp (program, arg_list);
    /* A função execvp só retorna se um erro ocorrer.  */
    fprintf (stderr, "um erro ocorreu em execvp\n");
    abort ();
  }
}

int main ()
{
  /* A lista e argumentos para ser passada ao comando "ls".  */
  char* arg_list[] = {
    "ls",     /* argv[0], o nome do programa.  */
    "-l", 
    "/",
    NULL      /* A lista de argumentos deve ser terminada com NULL.  */
  };

  while(1){
    char *line = NULL;  /* forces getline to allocate with malloc */
    size_t len = 0;     /* ignored when line = NULL */
    ssize_t read;

    // printf ("\nEnter string below [ctrl + d] to quit\n");

    printf ("> ");
    read = getline(&line, &len, stdin)

    if (read > 0){
      printf ("\n  read %zd chars from stdin, allocated %zd bytes for line : %s\n", read, len, line);
    }

    free (line);  /* free memory allocated by getline */
  }

  // /* Gera um processo filho executando o comando "ls".  Ignore o
  //    id do processo filho retornado.  */
  // spawn ("ls", arg_list); 

  // printf ("o programa principal terminou\n");

  return 0;
}