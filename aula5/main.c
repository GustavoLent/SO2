#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/* Gera um processo filho executando um novo programa.
   PROGRAM � o nome do programa a ser executado; ele
   ser� buscado no path. ARG_LIST � uma lista terminada
   em NULL de strings de caracteres a serem passados
   como a lista de argumentos do programa. Retorna o id
   do processo gerado.  */

int spawn(char *program, char **arg_list)
{
  pid_t child_pid;

  /* Duplicar este processo.  */
  child_pid = fork();
  if (child_pid != 0)
    /* Este � o processo pai.  */
    return child_pid;
  else
  {
    /* Agora execute PROGRAM,  buscando-o no path.  */
    execvp(program, arg_list);
    /* A fun��o execvp s� retorna se um erro ocorrer.  */
    fprintf(stderr, "um erro ocorreu em execvp\n");
    abort();
  }
}

void handleExit(char *line)
{
  if (strcmp(line, "exit") == 0)
  {
    exit(0);
  }
  return;
}

void handleNewline(char *line, int len)
{
  if (line[len - 1] == '\n')
  {
    line[len - 1] = '\0';
  }
}

int countWords(char *line)
{
  int count = 0;
  for (int i = 0; line[i] != '\0'; i++)
  {
    if (line[i] == ' ')
    {
      count++;
    }
  }
  return count;
}

char *getCommand(char *line)
{
  char str[strlen(line)];
  strcpy(str, line);

  return strtok(str, " ");
}

int main()
{
  /* A lista e argumentos para ser passada ao comando "ls".  */
  char *arg_list[] = {
      "ls", /* argv[0], o nome do programa.  */
      "-l",
      "/",
      NULL /* A lista de argumentos deve ser terminada com NULL.  */
  };

  char *pwd = getenv("PWD");
  char *line;
  size_t alocated_bytes = 0;
  ssize_t chars_read = 0;

  while (1)
  {
    line = NULL;        /* forces getline to allocate with malloc */
    alocated_bytes = 0; /* ignored when line = NULL */
    chars_read = 0;

    printf("[LentShell] %s$ ", pwd);
    chars_read = getline(&line, &alocated_bytes, stdin);

    if (alocated_bytes > 0)
    {
      handleNewline(line, chars_read);
      handleExit(line);

      int wordsQtd = countWords(line);
      printf("words: %d\n", wordsQtd);

      char *cmd = getCommand(line);

      // int value = atoi(line);
      // char arr[value];
      // printf("no error\n");
      // arr[0] = 'a';
      // printf("%c", arr[0]);

      printf("\nread %zd chars from stdin, allocated %zd bytes for line : %s\n", chars_read, alocated_bytes, line);
    }

    free(line); /* free memory allocated by getline */
  }

  // /* Gera um processo filho executando o comando "ls".  Ignore o
  //    id do processo filho retornado.  */
  // spawn ("ls", arg_list);

  // printf ("o programa principal terminou\n");

  return 0;
}
