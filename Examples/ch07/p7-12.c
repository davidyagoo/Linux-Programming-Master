#include "ch07.h"
volatile pid_t pkid;
sig_atomic_t killed=0;
sigjmp_buf again;
void sig_handler(int sig, siginfo_t *sip, void *extra)
{
    printf ("%d got a signal: %d, ", getpid(), sig);
    fflush(stdout); 
    psignal(sig, "");
    if (sip->si_code == SI_USER){
        printf("\tsi_code %d, signal was sened by kill(), sender is %d\n",
                 sip->si_code, sip->si_pid);
        return;
    }
    printf ("\tsi_code %d, ", sip->si_code);
    switch (sig){  /* �藍�P���T���A�ھ�si_code���ȹ�T����]�i�椣�P���P�O */
    case SIGFPE: 
       if (sip->si_code==FPE_INTDIV)
          printf ("integer divided by zero");
       else if (sip->si_code==FPE_FLTDIV)
          printf ("floating point divided by zero");
       else /* �K �䥦���� */
          printf ("overflow or something else");
       printf (" at address %x\n", sip->si_addr);
       siglongjmp(again, 1); /* �Ǧ^�ɲ��L�X���I */
       break;
    case SIGSEGV: 
       if (sip->si_code == SEGV_MAPERR)
           printf ("unmapped address:");
       else
           printf ("unprivileged access address:");
       printf("%x\n", sip->si_addr);
       exit(0);   /* �o�O�̫�ǰe���T���A�{���q�o�̲פ���� */
    case SIGCHLD:
       if (sip->si_code == CLD_KILLED)
           printf("\tChild %d was killed\n",sip->si_pid);
       else 
           printf("\tChild exited with exit_status: %d\n",sip->si_status);
       killed = 1;         /* �]�w�T���B�z�����Ч� */
       break;
    default:
       printf("others\n");
       exit(0);
   }
}
void (*fun)(int)=NULL;   /* �a�Ū���ƫ��� */
int a, b=0;
int main(void)
{
   struct sigaction sa;
   /* �]�w�T������X */
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_SIGINFO;         /* �ϥαa�T�ӰѼƪ��T������X */
   sa.sa_sigaction = sig_handler;
   sigaction(SIGCHLD, &sa, 0);
   sigaction(SIGFPE, &sa, 0);
   sigaction(SIGSEGV, &sa, 0);
   /* �إߤ@�Ӥl�����,�M��kill�� */ 
   if (pkid = fork()){     /* ������� */
       printf("I am father,My pid=%d. \n",getpid());
       printf("I forked and killed a child whose pid is %d\n", pkid);
       kill(pkid,SIGTERM); 
       while (!killed);              /* ���ݪ���l��������} */
       kill(getpid(),SIGFPE);
       if (sigsetjmp(again,1))      /* �]�w�D���������ಾ���� */
          goto L1;
       a=a/b;            /* �B�I�ҥ~��N�q�T������X�Ǧ^��W�@�ԭz */ 
L1:
      (*fun)(a);        /* �ū��бN�ɭP��ƩI�s���ͬq��, �T������X���Ǧ^ */
   } else               /* �l����� */
       while(1);        /* �l��������ݳQkill */
}
