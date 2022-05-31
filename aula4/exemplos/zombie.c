#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
  pid_t child_pid;

  /* Cria um processo filho.  */
  child_pid = fork ();
  if (child_pid > 0) {
    /* Este é o processo pai. Dormir por um minuto.  */
    sleep (60);
  }
  else {
    /* Este é o processo filho. Sair imediatamente.  */
    exit (0);
  }
  return 0;
}