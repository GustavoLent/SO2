/*
	Sistemas Operacionais II - Davi Duarte de Paula
	Trabalho 02 - Simulador de sistema de arquivos

	Gustavo Lima Lent & José Roberto Fernandes Russino
	Primeiro semestre de 2022

	-- Comandos:
	- mkdir:		Criar diretório (nome)
	- mkfile:	Criar arquivo (nome, tamanho)
	- rmdir:		Excluir um diretório (nome)
	- rmfile:	Excluir um arquivo (nome)
	- ls:			Listar arquivos e diretórios
	- showset	Mostrar setores ocupados pelo arquivo (nome)
	- lset			Mostrar mapa de setores livres e ocupados
	- help			Exibir o guia de ajuda
	- exit			Encerrar o terminal
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define INPUT_LABEL "[SisArq] $ "
#define MAX_LINE_SIZE 256
#define MAX_ARGS 256

#define SECTOR_BYTES_SIZE 508
#define SECTOR_NEXTSECTOR_NULL -1
#define DISK_AMOUNT_OF_SECTORS 256

#define FREE_SECTOR_INDICATOR '0'
#define USED_SECTOR_INDICATOR '1'

#define DIR_SEPARATOR '/'

#define DISK_RESERVED_SPACE 10

#define ROOT_DIR_NAME "~"
#define ROOT_DIR_SECTOR_OFFSET 9

#define FOLDER_CONTENT_NAME_SIZE 13
#define FOLDER_CONTENT_CREATIONDATE_SIZE 10
#define FOLDER_CONTENT_SIZE_NULL -1
#define FOLDER_CONTENT_ADDRESS_NULL -1
#define FOLDER_CONTENT_TYPE_FOLDER '1'
#define FOLDER_CONTENT_TYPE_FILE '0'
#define FOLDER_CONTENT_USED_BYTES 32

#define SHOWSET_ITEMS_PER_LINE 10
#define MKDIR_MAX_DEPTH 16

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
	char name[FOLDER_CONTENT_NAME_SIZE];
	int size;
	char creationDate[FOLDER_CONTENT_CREATIONDATE_SIZE];
	int address;
} FOLDER_CONTENT;

FOLDER_CONTENT newFolderContent()
{
	FOLDER_CONTENT fc;

	fc.type = '\0';
	memset(fc.name, '\0', sizeof(fc.name));
	fc.size = FOLDER_CONTENT_SIZE_NULL;
	memset(fc.creationDate, '\0', sizeof(fc.creationDate));
	fc.address = FOLDER_CONTENT_ADDRESS_NULL;

	return fc;
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

// Helper functions

char *ltrim(char *s)
{
	while (isspace(*s))
		s++;
	return s;
}

char *rtrim(char *s)
{
	char *back = s + strlen(s);
	while (isspace(*--back))
		;
	*(back + 1) = '\0';
	return s;
}

char *trim(char *s)
{
	return rtrim(ltrim(s));
}

/**
	Split the Line in the SplitWhere. Fill the Array with the splitted parts.

	Returns the amount of the parts when success, and -1 when had an error.
	The error will happen when tries to append values into an index greater than ArraySize.
*/
int split(char *arr[], int arrSize, char *line, char *splitWhere)
{
	char *token;
	int i = 0;
	int errorStatus = 0;

	token = strtok(line, splitWhere);
	while (token != NULL)
	{
		if (i < arrSize)
		{
			arr[i++] = token;
			token = strtok(NULL, splitWhere);
		}
		else
		{
			errorStatus = -1;
		}
	}

	if (i < arrSize)
	{
		arr[i + 1] = NULL;
	}
	else
	{
		errorStatus = -1;
	}

	return i;
}

/**
	Iterates over the Array, assigning NULL to the values.
*/
void clearArray(char *arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = NULL;
	}

	return;
}

// System functions

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

DISK initializeDisk(char *sectorsAlocationTable)
{
	DISK disk;

	for (int i = 0; i < DISK_AMOUNT_OF_SECTORS; i++)
	{
		disk.sectors[i] = newSector();

		if (i < DISK_RESERVED_SPACE)
		{
			sectorsAlocationTable[i] = USED_SECTOR_INDICATOR;
			// the initial sectors are allocated to the system
		}
	}

	return disk;
}

int getNextFreeSectorOffset(char *sectorsAlocationTable, int sectorsAlocationTableSize)
{
	int found = 0;
	int idx;

	for (idx = 0; idx < sectorsAlocationTableSize && found == 0; idx++)
	{
		if (sectorsAlocationTable[idx] == FREE_SECTOR_INDICATOR)
		{
			found = 1;
		}
	}

	if (found == 1)
	{
		return idx;
	}

	return -1; // Not Found
}

/**
	In the given directory, indexed in the disk by directorySectorOffset, search for the subdirectory by name.

	If found, return the index of the subdirectory in the disk. Else, returns -1.
 */
int getSubdirSectorOffsetOnDirectoryByName(DISK disk, int directorySectorOffset, char *dirname)
{
	SECTOR s = disk.sectors[directorySectorOffset];
	printf("sector [%d] content: %s\n", directorySectorOffset, s.bytes);

	char *dirBytesContent = s.bytes;
	int contentFrom = 0;
	int contentTo = FOLDER_CONTENT_USED_BYTES - 1;

	// while (dirBytesContent[contentFrom] != NULL)
	// {
	// 	char *childBytes[FOLDER_CONTENT_USED_BYTES];

	// 	strncpy(childBytes, dirBytesContent + contentFrom, contentTo);

	// 	printf("childBytes: %s\n", childBytes);

	// 	contentFrom += FOLDER_CONTENT_USED_BYTES;
	// 	contentTo += FOLDER_CONTENT_USED_BYTES;
	// }

	return -1;
}

/**
 Returns -1 if no free bytes
 */
int getSectorFreeByteOffset(char *bytes)
{

	for (int i = 0; i < SECTOR_BYTES_SIZE; i++)
	{
		if (bytes[i] == '\0')
		{
			return i;
		}
	}

	return -1; // no free bytes on the sector
}

/**
Errors codes:
	(-1) No sector available
	(-2) Full directory
 */
int createSubdirOnDirectory(
		DISK *disk,
		int directorySectorOffset,
		char *subdirName,
		char *sectorsAlocationTable,
		int sectorsAlocationTableSize)
{
	printf("createSubdirOnDirectory\n");

	printf("\nsubdirName: %s\n", subdirName);
	printf("sizeof(subdirName): %ld\n", sizeof(subdirName));
	printf("name char: %c\n", subdirName[0]);

	int nextFreeSector = getNextFreeSectorOffset(sectorsAlocationTable, sectorsAlocationTableSize);
	printf("nextFreeSector: %d\n", nextFreeSector);

	if (nextFreeSector == -1)
	{
		return -1;
	}

	SECTOR *sectorPointer = &disk->sectors[directorySectorOffset];
	int freeByteOffset = getSectorFreeByteOffset(sectorPointer->bytes);
	printf("freeByteOffset: %d\n", freeByteOffset);

	if (freeByteOffset == -1)
	{
		return -1;
	}

	char data[FOLDER_CONTENT_USED_BYTES] = {''};
	data[0] = FOLDER_CONTENT_TYPE_FOLDER; // Set type as DIRECTORY

	int nameOffset = 1;

	for (int i = 0; i < FOLDER_CONTENT_NAME_SIZE; i++)
	{ // iterate over data and the subdirName // users
		char namechar = i < sizeof(subdirName) - 1 ? subdirName[i] : ' ';
		data[nameOffset + i] = namechar;
	} // Set NAME

	int newdirSectorAddressOffset = 28;
	char address[4] = {' '};
	sprintf(address, "%d", nextFreeSector);
	printf("address: %s\n\n", address);

	for (int i = 0; i < 4; i++)
	{ // define the address
		data[i + newdirSectorAddressOffset] = address[i];
	} // Set ADDRESS on DISK

	printf("data after bytes: %s\n", data);

	for (int i = 0; i < FOLDER_CONTENT_USED_BYTES; i++)
	{ // iterate over sector bytes
		sectorPointer->bytes[i + freeByteOffset] = data[i];
	}

	sectorsAlocationTable[nextFreeSector] = USED_SECTOR_INDICATOR;

	printf("sector bytes: %s\n", sectorPointer->bytes);

	printf("\n");

	return 0;
}

void showset(char *sectorsAlocationTable, int size)
{
	printf("Sectors status:\n");
	int itemsCount = 0;
	int newLineCtrl = 0;

	for (int i = 0; i < size; i++)
	{
		char index[16];

		if (i >= 100)
		{
			sprintf(index, "%d", i);
		}
		else if (i >= 10)
		{
			sprintf(index, "0%d", i);
		}
		else
		{
			sprintf(index, "00%d", i);
		}

		char status = sectorsAlocationTable[i];
		printf("[%s ", index);

		if (status == FREE_SECTOR_INDICATOR)
		{
			printf("FREE] ");
		}
		else
		{
			printf("USED] ");
		}

		itemsCount++;

		if (itemsCount == SHOWSET_ITEMS_PER_LINE)
		{
			printf("\n");
			itemsCount = 0;
			newLineCtrl = 1;
		}
		else
		{
			newLineCtrl = 0;
		}
	}

	if (newLineCtrl == 0)
	{
		printf("\n");
	}

	return;
}

/**
	Creates a new directory.

	Returns 0 if success, and -1 if error.
 */
int mkdir(
		DISK *diskPointer,
		char *args[],
		char *sectorsAlocationTable,
		int sectorsAlocationTableSize)
{
	// printf("mkdir given args %d: %s\n", 0, args[0]);
	// printf("mkdir given args %d: %s\n", 1, args[1]);

	char *pathAndDirname = args[1];
	char *pathAndDirnameTokens[MKDIR_MAX_DEPTH];

	int tokensSize = split(pathAndDirnameTokens, MKDIR_MAX_DEPTH, args[1], "/");

	if (tokensSize < 2)
	{
		printf("%s Error: must give a path and a dirname to \"mkdir\", separated by \"/\". Example \"mkdir ~/user/freddie\"\n", INPUT_LABEL);
		return -1;
	}

	if (strcmp(pathAndDirnameTokens[0], ROOT_DIR_NAME) != 0)
	{
		printf("%s Error: the given path on \"mkdir\" must start with the base directory \"%s\"\n", INPUT_LABEL, ROOT_DIR_NAME);
		return -1;
	}

	if (tokensSize == 2)
	{ // will create a dir on rootdir
		printf("will create a dir on rootdir\n");

		char *newdirName = pathAndDirnameTokens[1];

		if (sizeof(newdirName) > FOLDER_CONTENT_NAME_SIZE)
		{
			printf("%s Error: the new directory's name is too big. Max chars set to %d", INPUT_LABEL, FOLDER_CONTENT_NAME_SIZE);
			// todo return error
		}

		int res = createSubdirOnDirectory(diskPointer, ROOT_DIR_SECTOR_OFFSET, newdirName, sectorsAlocationTable, sectorsAlocationTableSize);

		printf("after mkdir: %s\n", diskPointer->sectors[9].bytes);

		return res;
	}

	// creates a new dir in N depth
	// for (int i = 0; i < mkdirArgsSize - 1; i++)
	// {
	// 	char *dir = mkdirArgs[i];
	// 	int sectorOffset = getSubdirSectorOffsetOnDirectoryByName(disk, dir);

	// 	if (sectorOffset == -1)
	// 	{
	// 		printf("%s Error: check the given path, directory \"%s\" not found\n", INPUT_LABEL, dir);
	// 		return -1;
	// 	}
	// }

	// printf("mkdirArgs %d: %s\n", 0, mkdirArgs[0]);
	// printf("mkdirArgs %d: %s\n", 1, mkdirArgs[1]);

	return 0;
}

// End of System functions

int main()
{
	// Command variables
	char line[MAX_LINE_SIZE];
	char *args[MAX_ARGS];
	char *token;
	int i;
	char *cmd;

	// System variables
	printf("Initializing Sector Alocation Table...");
	char sectorsAlocationTable[DISK_AMOUNT_OF_SECTORS];
	initializeSectorsAlocationTable(sectorsAlocationTable, DISK_AMOUNT_OF_SECTORS);
	printf("\tOK!\n");

	printf("Initializing Disk...");
	DISK disk = initializeDisk(sectorsAlocationTable);
	printf("\t\t\tOK!\n");

	while (1)
	{
		printf("%s", INPUT_LABEL);

		// Get the command
		fgets(line, sizeof(line), stdin);

		// Skip if the input where only ENTER
		if (line[0] == '\n')
		{
			continue;
		}

		// Replace ENTER with END STRING
		for (i = 0; line[i] != '\n'; i++)
		{
		}
		line[i] = '\0';

		// Get tokens from command (as ARGS)
		split(args, MAX_ARGS, line, " ");

		// Identify the command
		if (strcmp(args[0], "showset") == 0)
		{
			showset(sectorsAlocationTable, DISK_AMOUNT_OF_SECTORS);
		}
		else if (strcmp(args[0], "mkdir") == 0)
		{
			if (args[1] == NULL)
			{
				printf("%sError: \"mkdir\" missing parameter path/dir_name\n", INPUT_LABEL);
			}
			else
			{

				mkdir(&disk, args, sectorsAlocationTable, DISK_AMOUNT_OF_SECTORS);
			}
		}
		else if (strcmp(args[0], "clear") == 0)
		{
			printf("\e[1;1H\e[2J");
		}
		else if (strcmp(args[0], "exit") == 0)
		{
			return 0;
		}
		else /* default: */
		{
			printf("%s Error: command \"%s\"not found", INPUT_LABEL, args[0]);
		}

		clearArray(args, MAX_ARGS);
	}
	return 0;
}
