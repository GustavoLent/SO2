// Alunos:	Gustavo Lima Lent
//			Jose Roberto Fernandes Russino
// Data:	--/07/2022*
// Trabalho 02 - Simulador de sistema de arquivos
// Sistemas Operacionais II - Davi Duarte de Paula

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SECTOR_BYTES_SIZE 508
#define SECTOR_NEXTSECTOR_NULL -1
#define DISK_AMOUNT_OF_SECTORS 256
#define FREE_SECTOR_INDICATOR '0'
#define USED_SECTOR_INDICATOR '1'

int mkdir_exec(char *name, char *size);		// Criar diretório (nome)
int mkfile_exec(char *name, char *size);	// Criar arquivo (nome, tamanho)
int rmdir_exec(char *name, char *size);		// Excluir um diretório (nome)
int rmfile_exec(char *name, char *size);	// RMFILE: Excluir um arquivo (nome)
int ls_exec(char *name, char *size);			// LS: Listar arquivos e diretórios
int showset_exec(char *name, char *size); // SHOWSET: Mostrar setores ocupados pelo arquivo (nome)
int lset_exec(char *name, char *size);		// LSET: Mostrar mapa de setores livres e ocupados
int help_exec(char *name, char *size);		// HELP: Exibir o guia de ajuda
int exit_exec(char *name, char *size);		// EXIT:

typedef struct
{
	char bytes[SECTOR_BYTES_SIZE];
	int nextSector;
} SECTOR;

typedef struct
{
	SECTOR sectors[DISK_AMOUNT_OF_SECTORS];
} DISK;

typedef struct
{
	char type;
	char nome[15];
	int size;
	char creationDate[10];
} FOLDER_CONTENT;

SECTOR newSector()
{
	SECTOR s;
	memset(s.bytes, '\0', sizeof(s.bytes));

	s.nextSector = SECTOR_NEXTSECTOR_NULL;
	return s;
}

void initializeSectorsAlocationTable(char *sectorsAlocationTable, int size)
{

	for (int i = 0; i < size; i++)
	{
		sectorsAlocationTable[i] = FREE_SECTOR_INDICATOR;
	}

	return;
}

void initializeDisk() {} // para inicializar o disco, precisa do diretório /

struct actions
{
	char *cmd;
	int (*actions)(char *name, char *size);
} cmd_list[] = {
		{"mkdir", mkdir_exec},
		{"mkfile", mkfile_exec},
		{"rmdir", rmdir_exec},
		{"rmfile", rmfile_exec},
		{"ls", ls_exec},
		{"showset", showset_exec},
		{"lset", lset_exec},
		{"help", help_exec},
		{"exit", exit_exec},
		{NULL, NULL}};

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

int main()
{
	char sectorsAlocationTable[DISK_AMOUNT_OF_SECTORS];
	initializeSectorsAlocationTable(sectorsAlocationTable, DISK_AMOUNT_OF_SECTORS);

	printf("text: %c\n", sectorsAlocationTable[2]);

	SECTOR s = newSector();
	strncpy(s.bytes, "Ola Mundo!", sizeof("Ola Mundo!"));
	printf("text: %s\n", s.bytes);
}

/*
int main()
{
	char line[256];
	char *args[256];
	char *token;
	int i, search;
	char *cmd;

	while (1)
	{
		printf("[SisArq] $ ");

		// captura o comando digitado
		fgets(line, sizeof(line), stdin);

		// processa o enter sozinho
		if (line[0] == '\n')
			continue;

		// substitui o enter por fim de linha
		for (i = 0; line[i] != '\n'; i++)
			;
		line[i] = '\0';

		// separa a linha digitada em tokens
		i = 0;
		token = strtok(line, " ");
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
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
					fprintf(stderr, "[SisArq] %s %s %s: failed\n", args[0], args[1], args[2]);
			}
		}

		if (search == 0)
			printf("[SisArq] not found: %s\n", args[0]);
	}
	return 0;
}
*/