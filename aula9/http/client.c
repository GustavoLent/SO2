#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define SA struct sockaddr

void func(int sockfd, char *message)
{
  // Send to the server
  int length = strlen(message) + 1;
  write(sockfd, &length, sizeof(length));

  /* Escreve a string. */
  write(sockfd, message, length);
}

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    fprintf(stderr, "Indique o endereço do host, a porta e a mensagem!\n");
    exit(-1);
  }

  int PORT = atoi(argv[1]);
  char *address = argv[2];
  char *message = argv[3];

  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;

  // socket create and verification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    printf("Erro ao criar o socket...\n");
    exit(0);
  }
  else
  {
    printf("Socket criado com sucesso!\n");
  }

  bzero(&servaddr, sizeof(servaddr));

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(address);
  servaddr.sin_port = htons(PORT);

  // connect the client socket to server socket
  if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
  {
    printf("Erro ao conectar com o servidor...\n");
    exit(0);
  }
  else
    printf("Conectado ao servidor!\n");

  // function for chat
  func(sockfd, message);

  // close the socket
  close(sockfd);
}