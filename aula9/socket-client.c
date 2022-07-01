#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

/* Escreve TEXT para o socket dado pelo descritor de arquivo SOCKET_FD. */
void write_text (int socket_fd, const char* text) {
	
	/* Escreve o número de bytes na string, incluindo o terminador nulo */
	int length = strlen (text) + 1;
	write (socket_fd, &length, sizeof (length));

	/* Escreve a string. */
	write (socket_fd, text, length);
}

int main (int argc, char* const argv[])
{
	const char* const socket_name = argv[1];
	const char* const message = argv[2];
	int socket_fd;
	struct sockaddr_un name;

	/* Cria um socket. 
	 * Cliente com Socket de Espaço de Nomes Local 
	 */
	
	socket_fd = socket (PF_LOCAL, SOCK_STREAM, 0);
	/* Guarda o nome do servidor no endereço do socket. */
	
	name.sun_family = AF_LOCAL;
	strcpy (name.sun_path, socket_name);
	/* Conecta o socket. 
	 * Obs: no código original falta o cast de &name 
	 */
	
	connect (socket_fd, (struct sockaddr *) &name, SUN_LEN (&name));
	
	/* Escreve o texto da linha de comando para o socket. */
	write_text (socket_fd, message);
	close (socket_fd);
	return 0;
}
