#include <stdio.h>
#include <stdlib.h>

// echo $SERVER_NAME
// export SERVER_NAME=server.unesp.br
// echo $SERVER_NAME

int main ()
{
  char* server_name = getenv ("SERVER_NAME");
  if (server_name == NULL) 
    /* A variável de ambiente SERVER_NAME não foi configurada. Use o padrão.  */
    server_name = "server.my-company.com";

  printf ("accessando servidor %s\n", server_name);
  /* Acesse o servidor aqui...  */

  return 0;
}