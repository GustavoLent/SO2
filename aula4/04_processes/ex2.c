#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int spawn(char *program, char **arg_list)
{
    pid_t child_pid;
    /* Duplicar este processo. */
    child_pid = fork();
    if (child_pid != 0)
        /* Este é o processo pai. */
        return child_pid;
    else
    {
        /* Agora execute PROGRAM, buscando-o no path. */
        execvp(program, arg_list);
        /* A função execvp só retorna se um erro ocorrer. */
        fprintf(stderr, "um erro ocorreu em execvp\n");
        abort();
    }
}

int main()
{
    /* A lista e argumentos para ser passada ao comando "ls". */
    char *arg_list[] = {
        "ls", /* argv[0], o nome do programa. */
        "-l",
        "/",
        NULL /* A lista de argumentos deve ser terminada com NULL. */
    };

    int ret1, status1;

    printf("> \"ls\" will be called\n");
    spawn("ls", arg_list);

    printf("> will call the \"wait\"\n");
    ret1 = wait(&status1);

    printf("> ended waiting...\n");

    return 0;
}
