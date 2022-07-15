// Alunos:	Gustavo Lima Lent
//			Jose Roberto Fernandes Russino
// Data:	--/07/2022*
// Trabalho 02 - Simulador de sistema de arquivos
// Sistemas Operacionais II - Davi Duarte de Paula

// alô

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int mkdir_exec (char *name, char *size); // Criar diret�rio (nome)
int mkfile_exec(char *name, char *size); // Criar arquivo (nome, tamanho)
int rmdir_exec(char *name, char *size); // Excluir um diret�rio (nome)
int rmfile_exec(char *name, char *size); // RMFILE: Excluir um arquivo (nome)
int ls_exec(char *name, char *size); // LS: Listar arquivos e diret�rios
int showset_exec(char *name, char *size); // SHOWSET: Mostrar setores ocupados pelo arquivo (nome)
int lset_exec(char *name, char *size); // LSET: Mostrar mapa de setores livres e ocupados
int help_exec(char *name, char *size); // HELP: Exibir o guia de ajuda
int exit_exec(char *name, char *size); // EXIT: 

struct actions {
  char *cmd;
  int (*actions)(char *name, char *size);
} cmd_list[] = {
    {"mkdir",mkdir_exec},
    {"mkfile",mkfile_exec},
    {"rmdir",rmdir_exec},
    {"rmfile",rmfile_exec},
    {"ls",ls_exec},
    {"showset",showset_exec},
    {"lset",lset_exec},
    {"help",help_exec},
    {"exit",exit_exec},
    {NULL,NULL}
};

int mkdir_exec(char *name, char *size)
{
	return 0;
}
int mkfile_exec(char *name, char *size)
{
	return 0;
}
int rmdir_exec(char *name, char *size)
{
	return 0;
}
int rmfile_exec(char *name, char *size)
{
	return 0;
}
int ls_exec(char *name, char *size)
{
	return 0;
}
int showset_exec(char *name, char *size)
{
	return 0;
}
int lset_exec(char *name, char *size)
{
	return 0;
}
int help_exec(char *name, char *size)
{
	return 1;
}
int exit_exec(char *name, char *size)
{
	return 0;
}



int main ()
{
  char line[256];
  char *args[256];
  char *token;
  int i, search;
  char *cmd;



  while (1)
    {
    	printf ("[SisArq] $ ");

    	// captura o comando digitado
    	fgets (line, sizeof (line), stdin);


    	// processa o enter sozinho
    	if (line[0] == '\n') continue;


    	// substitui o enter por fim de linha
    	for (i = 0; line[i] != '\n'; i++);
    	line[i] = '\0';


    	// separa a linha digitada em tokens
    	i = 0;
    	token = strtok (line, " ");
    	while (token != NULL)
		{
	  		args[i++] = token;
	  		token = strtok (NULL, " ");
		}
      	args[i++] = NULL;


		// processa os comandos digitados
		search = 0;
      	for (struct actions *ptr = cmd_list; ptr->cmd != NULL; ptr++)
		{ 
        	if (strcmp(ptr->cmd, args[0]) == 0)
            {
                search = 1;
                if ((ptr->actions)(args[1], args[2]) != 0)
				fprintf (stderr, "[SisArq] %s %s %s: failed\n", args[0], args[1], args[2]);
			}
		}
		
     	if (search == 0) printf("[SisArq] not found: %s\n", args[0]);

	}
		return 0;

}

