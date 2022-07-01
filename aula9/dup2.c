#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	int fds[2];
	pid_t pid;
	
	pipe(fds);
	pid= fork();
	
	if(pid == (pid_t) 0){
		close(fds[1]);
		
		dup2(fds[0], STDIN_FILENO);
		execlp("sort", "sort", 0);		
	} else {
		FILE *stream;
		close(fds[0]);
		
		stream = fdopen(fds[1], "w");
		fprintf(stream, "Este é um teste.\n");
		fprintf(stream, "Olá mundo!\n");
		fprintf(stream, "Meu cachorro é barbeiro\n");
		fprintf(stream, "Este programa tem pulgas.\n");
		fprintf(stream, "Um peixe, três sapos e dois caramujos.\n");
		fflush(stream);
		
		close(fds[1]);
		waitpid(pid, NULL, 0);
	}
	
	return 0;	
}
