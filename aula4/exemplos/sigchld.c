#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

sig_atomic_t child_exit_status;

void clean_up_child_process (int signal_number)
{
  /* Limpa o processo filho.  */
  int status;
  wait (&status);
  /* Guarda o código de saída em uma variável global.  */
  child_exit_status = status;
}

int main ()
{
  /* Manipula SIGCHLD chamando clean_up_child_process.  */
  struct sigaction sigchld_action;
  memset (&sigchld_action, 0, sizeof (sigchld_action));
  sigchld_action.sa_handler = &clean_up_child_process;
  sigaction (SIGCHLD, &sigchld_action, NULL);

  /* Agora faça coisas, incluindo criar um processo filho com fork.  */
  /* ...  */

  return 0;
}