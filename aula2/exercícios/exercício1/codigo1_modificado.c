#include <stdio.h>
#include <unistd.h>

// STD OUT TEM BUFFER, POR ISSO, ELE NÃO É PRINTADO AO VIVO
// CORRIGIMOS ISSO INSERINFO UM FFLUSH
int main()
{
       while(1)
       {
               printf(".");
               fflush(stdout);
               usleep(10000);
       }
}