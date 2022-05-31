#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
int main()
{
        int fd;
        fd = open ("arquivoentrada.txt", O_RDONLY);
        if (fd == -1) {
                /* Abertura falhou. Imprima mensagem de erro e saia. */
                fprintf (stderr, "erro abrindo arquivo: %s\n", strerror (errno));
                exit (1);
        }
}