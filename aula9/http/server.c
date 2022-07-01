#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX 80
#define SA struct sockaddr
#define LOCALHOST "127.0.0.1"
#define LISTEN_QUEUE 5

int server(int connfd)
{
  while (1)
  {
    int length;
    char *text;
    /*
      Primeiro, lê o tamanho de uma mensagem de texto do socket.
      Se a leitura retorna zero, o cliente fechou a conexão.
    */
    if (read(connfd, &length, sizeof(length)) == 0)
    {
      return 0;
    }

    /* Aloca o buffer para armazenar o texto. */
    text = (char *)malloc(length);
    /* Lê o texto, e o imprime. */

    read(connfd, text, length);
    printf("[Client] %s\n", text);
    /* Se o cliente enviou a mensagem "quit", terminamos. */

    int shouldQuit = strcmp(text, "quit");
    free(text);

    if (!shouldQuit)
    {
      return 1;
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf(stderr, "Indique a porta a ser ouvida quando chamar o programa!\n");
    exit(-1);
  }

  int PORT = atoi(argv[1]);
  struct sockaddr_in servaddr, cli;

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd == -1)
  {
    printf("Falha ao criar o socket...\n");
    exit(0);
  }
  else
  {
    printf("Socket criado com sucesso!\n");
  }

  bzero(&servaddr, sizeof(servaddr));

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(LOCALHOST);
  servaddr.sin_port = htons(PORT);

  // Binding newly created socket to given IP and verification
  if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
  {
    printf("Ero ao fazer o Bind do socket...\n");
    exit(0);
  }
  else
  {
    printf("Sucesso ao fazer o Bind do socket!\n");
  }

  // Now server is ready to listen and verification
  if ((listen(sockfd, LISTEN_QUEUE)) != 0)
  {
    printf("Erro ao iniciar a escuta...\n");
    exit(0);
  }
  else
  {
    printf("O servidor está disponível na porta %d!\n", PORT);
  }

  int client_sent_quit_message;

  do
  {
    int len = sizeof(cli);
    int connfd = accept(sockfd, (SA *)&cli, &len);

    if (connfd < 0)
    {
      printf("Erro ao conectar com cliente...\n");
      exit(0);
    }
    else
    {
      printf("Cliente conectado!\n");
    }

    /* Manipula a conexão. */
    client_sent_quit_message = server(connfd);

    /* Fecha nossa ponta da conexão. */
    close(connfd);
  } while (!client_sent_quit_message);

  close(sockfd);
}