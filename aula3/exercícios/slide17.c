#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

char* read_from_file (const char* filename, size_t length)
{

  /* 1. Alocar o buffer  */
  char* buffer = (char*) malloc (length);

  if (buffer == NULL)
    return NULL;

  /* 2. Abrir o arquivo  */
  int fd = open (filename, O_RDONLY);
    
  if (fd == -1) {
    /* Se o passo 2 falhar, é preciso desalocar o buffer alocado no passo 1 antes de retornar  */
    free (buffer);
    return NULL;
  }

  /* 3. Ler do arquivo para o buffer  */
  size_t   = read (fd, buffer, length);

  if (bytes_read != length) {
    /* Se o passo 3 falhar, é preciso também fechar o arquivo, antes de retornar  */
    free (buffer);
    close (fd);
    return NULL;
  }

  /* 4. Fechar o arquivo  */
  close (fd);

  /* 5. Retornar o buffer  */
  return buffer;
}

int main(){
  char *return_value = read_from_file("arquivo_qualquer.txt", 3);

  if (return_value == NULL){
    fprintf(stderr, "Erro durante a leitura: %s\n", strerror (errno));
  }

  fprintf(" %s\n", return_value);
}