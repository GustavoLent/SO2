#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

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
    int status;
    wait(&status);

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

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while (isspace((unsigned char)*str))
    str++;

  if (*str == 0) // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

void getWordsListSize(char *line, int *amountOfWords, int *biggestWord)
{
  int _amountOfWords = 0;
  int _biggestWord = 0;
  int currWordSizeCount = 0;
  int foundSpace = 0;

  for (int i = 0; line[i] != '\0'; i++)
  {
    if (line[i] == ' ' && foundSpace == 1)
    {
      continue; // skip consecutive spaces
    }

    if (line[i] == ' ')
    {
      foundSpace = 1;
      _amountOfWords++;
      if (currWordSizeCount > _biggestWord)
      {
        _biggestWord = currWordSizeCount;
      }
      currWordSizeCount = 0;
    }
    else
    {
      foundSpace = 0;
      currWordSizeCount++;
    }
  }

  if (currWordSizeCount > _biggestWord)
  {
    _biggestWord = currWordSizeCount;
  }

  *amountOfWords = _amountOfWords + 1; // one space = two words
  *biggestWord = _biggestWord;

  return;
}

int main()
{
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
      char *trimmed = trimwhitespace(line);

      if (trimmed[0] == '\n' || trimmed[0] == '\0')
      {
        free(line);
        continue;
      }

      handleNewline(trimmed, chars_read);
      handleExit(trimmed);

      int amountOfWords, biggestWord;
      getWordsListSize(line, &amountOfWords, &biggestWord);

      char *words[amountOfWords + 1];
      char toCut[strlen(line)];
      strcpy(toCut, line);

      char *firstToken = strtok(toCut, " ");
      words[0] = (char *)malloc(strlen(firstToken));

      strcpy(words[0], firstToken);

      for (int i = 1; i < amountOfWords; i++)
      {
        char *token = strtok(NULL, " ");
        words[i] = (char *)malloc(strlen(token));

        strcpy(words[i], token);
      }

      words[amountOfWords + 1] = NULL;
      spawn(words[0], words);
    }

    free(line); /* free memory allocated by getline */
  }

  return 0;
}
