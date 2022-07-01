#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

int server(int client_socket)
{
	while (1)
	{
		int length;
		char *text;
		/*
			Primeiro, lê o tamanho de uma mensagem de texto do socket.
			Se a leitura retorna zero, o cliente fechou a conexão.
		*/

		if (read(client_socket, &length, sizeof(length)) == 0)
		{
			return 0;
		}

		/* Aloca o buffer para armazenar o texto. */

		text = (char *)malloc(length);

		/* Lê o texto, e o imprime. */

		read(client_socket, text, length);
		printf("%s\n", text);

		/* Se o cliente enviou a mensagem "quit" */

		if (!strcmp(text, "quit"))
		{
			free(text); /* Libera o buffer. */
			return 1;
		}
		else
		{
			free(text); /*	Libera o buffer. */
		}
	}
}

int main(int argc, char *const argv[])
{
	const char *const socket_name = argv[1];
	int socket_fd;

	struct sockaddr_in name;
	struct hostent *hostinfo;

	/* Cria o socket. */
	socket_fd = socket(PF_INET, SOCK_STREAM, 0);

	hostinfo = gethostbyname("localhost");

	if (hostinfo == NULL)
	{
		return 1;
	}
	else
	{
		name.sin_addr = *((struct in_addr *)hostinfo->h_addr);
	}

	name.sin_port = htons(8080);

	bind(socket_fd, (struct sockaddr *)&name, SUN_LEN(&name));
	/* Escuta por conexões. */

	listen(socket_fd, 5);
	/*
	 * Repetidamente aceita conexões, e cria um novo socket para lidar com cada cliente.
	 * Continua até um cliente enviar a mensagem “quit”.
	 */

	int client_sent_quit_message;

	do
	{
		struct sockaddr_un client_name;
		socklen_t client_name_len;
		int client_socket_fd;

		/* Aceita uma conexão. */
		client_name_len = sizeof(client_name);
		client_socket_fd = accept(socket_fd, (struct sockaddr *)&client_name, &client_name_len);

		/* Manipula a conexão. */
		client_sent_quit_message = server(client_socket_fd);

		/* Fecha nossa ponta da conexão. */
		close(client_socket_fd);
	}

	while (!client_sent_quit_message);

	/* Remove o arquivo de socket. */
	close(socket_fd);
	unlink(socket_name);

	return 0;
}

typedef struct server
{
	// file descriptor of the socket in passive
	// mode to wait for connections.
	int listen_fd;
} server_t;

int server_listen(server_t *server);

/**
 * Accepts new connections and then prints `Hello World` to
 * them.
 */

int server_accept(server_t *server)
{
	int err = 0;
	int conn_fd;
	socklen_t client_len;
	struct sockaddr_in client_addr;

	client_len = sizeof(client_addr);

	err =
			(conn_fd = accept(
					 server->listen_fd, (struct sockaddr *)&client_addr, &client_len));
	if (err == -1)
	{
		perror("accept");
		printf("failed accepting connection\n");
		return err;
	}

	printf("Client connected!\n");

	err = close(conn_fd);
	if (err == -1)
	{
		perror("close");
		printf("failed to close connection\n");
		return err;
	}

	return err;
}

/**
 * Main server routine.
 *
 *      -       instantiates a new server structure that holds the
 *              properties of our server;
 *      -       creates a socket and makes it passive with
 *              `server_listen`;
 *      -       accepts new connections on the server socket.
 *
 */
int main()
{
	int err = 0;
	server_t server = {0};

	err = server_listen(&server);
	if (err)
	{
		printf("Failed to listen on address 0.0.0.0:%d\n", PORT);
		return err;
	}

	for (;;)
	{
		err = server_accept(&server);
		if (err)
		{
			printf("Failed accepting connection\n");
			return err;
		}
	}

	return 0;
}
