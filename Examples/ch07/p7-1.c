#include "ch07.h"
volatile sig_atomic_t usr_interrupt = 0;   /* �����FSIGUSR1�T���ɳ]�w���ܼ� */
void sig_usr(int sig)                  /* SIGUSR1�T��������� */
{
   usr_interrupt = 1;
}
void child_function(void)        /* �l��������榹��� */
{
   printf("I'm here!  My pid is %d.\n", (int)getpid());
   kill(getppid(), SIGUSR1);     /* ���|������� */
   /* �~����� */
   puts("Bye, now....");
   exit(EXIT_SUCCESS);
}
int main(void)
{
   pid_t child_id;     
   signal (SIGUSR1, sig_usr);  /* �إ߰T������X */
   child_id = fork ();          /* �إߤl����� */
   if (child_id == 0)           /* �l����� */
      child_function();         /* �l��������Ǧ^ */
   while (!usr_interrupt) ;    /* ���ݤl������ǰe�T�� */  
   puts ("That's all!");       /* ����T�����~����� */
   return 0;
}

