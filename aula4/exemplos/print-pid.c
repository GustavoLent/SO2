#include <stdio.h>
#include <unistd.h>

int main ()
{
  printf ("O id do processo é %d\n", (int) getpid ());
  printf ("O id do pai do processo é %d\n", (int) getppid ());
  return 0;
}