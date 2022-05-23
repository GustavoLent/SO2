#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

sig_atomic_t sigusr1_count = 0;

void handler(int signal_number)
{
    ++sigusr1_count;
}

int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    sa.sa_handler = &handler;
    sigaction(SIGUSR1, &sa, NULL);

    for (int i = 0; i < 30000; i++)
    {
        usleep(1000);
    }

    printf("SIGUSR1 foi chamado %d vezes\n", sigusr1_count);
    return 0;
}
