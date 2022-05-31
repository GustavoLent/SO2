#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
  pid_t child_pid;

  printf ("o id do processo do programa principal é %d\n", (int) getpid ());

  child_pid = fork ();
  if (child_pid != 0) {
    printf ("este é o processo pai, com o id %d\n", (int) getpid ());
    printf ("o id do processo filho é %d\n", (int) child_pid);
  }
  else 
    printf ("este é o processo filho, com o id %d\n", (int) getpid ());

  return 0;
}