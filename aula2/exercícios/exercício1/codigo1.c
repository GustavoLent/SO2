#include <stdio.h>
#include <unistd.h>
int main()
{
       while(1)
       {
               printf(".");
               usleep(10000);
       }
}