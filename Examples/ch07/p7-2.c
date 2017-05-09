#include "ch07.h"
static void sig_usr(int); 
int main(void)
{
   if(signal(SIGUSR1, sig_usr) == SIG_ERR) /* �إ߰T��SIGUSR1������X */
      err_exit ("can't catch SIGUSR1\n");
   for(; ;)
      pause();
}
static void sig_usr(int signo)       /* �T��SIGUSR1������X */
{
   printf("received SIGUSR1\n");
   return;
}
