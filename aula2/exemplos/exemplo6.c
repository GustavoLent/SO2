#include <stdlib.h>
#include <unistd.h>

/* Um manipulador para um arquivo temporário criado com write_temp_file.  Nesta implementação, é apenas um descritor de arquivo.  */
typedef int temp_file_handle;

/* Escreve LENGTH bytes do BUFFER em um arquivo temporário. O arquivo temporário é desvinculado imediatamente. Retorna um manipulador para o arquivo temporário. */

temp_file_handle write_temp_file (char* buffer, size_t length)
{
  /* Cria nome de arquivo e arquivo. O XXXXXX será substituído por caracteres que tornem o nome de arquivo único.  */
  char temp_filename[] = "/tmp/temp_file.XXXXXX";
  int fd = mkstemp (temp_filename);
  /* Desvincula o arquivo imediatamente, de forma que ele seja removido quando o descritor de arquivo for fechado.  */
  unlink (temp_filename);
  /* Escreve o número de bytes do arquivo primeiro.  */
  write (fd, &length, sizeof (length));
  /* Agora escreve os dados.  */
  write (fd, buffer, length);
  /* Usa o descritor de arquivos como manipulador para o arquivo temporário.  */
  return fd;
}



/* Lê o conteúdo de um arquivo temporário TEMP_FILE criado como
   write_temp_file.  O valor de retorno é um novo buffer alocado daquele conteúdo, o qual o chamador precisa desalocar com free.
   *LENGTH é configurado com o tamanho do conteúdo, em bytes. O arquivo temporário é removido.  */

char* read_temp_file (temp_file_handle temp_file, size_t* length)
{

  char* buffer;
  /* O manipulador TEMP_FILE é um descritor de arquivo para o arquivo temporário.  */
  int fd = temp_file;
  /* Volta para o início do arquivo.  */
  lseek (fd, 0, SEEK_SET);
  /* Lê o tamanho dos dados no arquivo temporário.  */
  read (fd, length, sizeof (*length));
  /* Aloca um buffer e lê os dados.  */
  buffer = (char*) malloc (*length);
  read (fd, buffer, *length);
  /* Fecha o descritor de arquivos, o qual irá fazer com que o arquivo temporário desapareça.  */
  close (fd);
  return buffer;
}

int main ()
{
  int lenght = 3;

  temp_file_handle handler = write_temp_file("abc", 3);
  
  char * buffer = read_temp_file(handler, & lenght);
  printf("%s", buffer);
}