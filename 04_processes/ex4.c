#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

sig_atomic_t child_exit_status;

void clean_up_child_process(int signal_number)
{
    /* Limpa o processo filho. */
    int status;
    wait(&status);
    /* Guarda o código de saída em uma variável global. */
    child_exit_status = status;
}

int main()
{
    /* Manipula SIGCHLD chamando clean_up_child_process. */
    struct sigaction sigchld_action;

    memset(&sigchld_action, 0, sizeof(sigchld_action));
    sigchld_action.sa_handler = &clean_up_child_process;

    sigaction(SIGCHLD, &sigchld_action, NULL);

    pid_t child_pid;
    int i = 0;
    int shouldExit = 0;

    while (shouldExit != 1)
    {
        int t = -1;

        printf("Digite quantos segundos o filho deve viver (ou 0 para encerrar): ");
        while (t == -1)
        {
            scanf("%i", &t);
            shouldExit = (t >= 1) ? 0 : 1;
        }

        if (t == 0)
            return (0);

        i++;

        printf("Criando %dº processo filho, viverá %d segundos\n", i, t);
        child_pid = fork();

        if (child_pid == 0)
        {
            sleep(t);
            return (0);
        }
    }

    return 0;
}