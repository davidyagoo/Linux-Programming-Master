#include "ch07.h"
int main(void)
{
    sigset_t base_mask, waiting_mask, oldmask;
    int sig;
     /* ����ϥΪ̪����_. */
    sigemptyset (&base_mask);
    sigaddset (&base_mask, SIGQUIT);
    sigaddset (&base_mask, SIGINT);
    if (sigprocmask (SIG_BLOCK, &base_mask, &oldmask)<0 )
       err_exit("SIG_BLOCK error");
    printf(" I have blocked SIGQUIT and SIGINT, and\n you can try "
           "to send these two signals and wait for my reply.\n");
    sleep(10);
     /* �L�@�|���,�˵��O�_���a���T��. */
    printf("Let me see if there is any pending signal.\n");
    sigpending (&waiting_mask);
    for ( sig=1;sig<NSIG;sig++)
       if (sigismember (&waiting_mask, sig)){ 
          psignal(sig,"There is a pending signal" );
	       /* ��ӰT�����X�^��... */
       }
     /* �٭�T���̽�,�o�N��}SIGINT�MSIGTSTP */
    if (sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
       err_exit("SIG_SETMASK error");
    /* �Y�G���T��,�U�����{���X���|���� */
    printf("Ther is no suspending signal. BYE!\n");	
    exit(EXIT_SUCCESS);
}
