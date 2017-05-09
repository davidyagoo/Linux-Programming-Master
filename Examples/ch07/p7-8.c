#include "ch07.h"
#include "xmalloc.c"
int make_stack_overflow(void)
{
    int a[100000];
    static int n;
    a[100000-1] = make_stack_overflow();   	/* ���k�I�s������|���� */
    return n++;
}
void set_ss_stack(stack_t *stk, stack_t *ostk)   /* �]�w���N�T�����| */
{
   if ((stk->ss_sp = (void *)xmalloc(SIGSTKSZ)) == NULL) /* �����N�T�����|���t�Ŷ� */
      perror("   xmalloc error");
   stk->ss_size = SIGSTKSZ; 
   stk->ss_flags = SS_ONSTACK;
   if (sigaltstack(stk, ostk) < 0)
      perror("   sigaltstack fail");
   return;
}
void check_ss_flags(char *str)    /* �˵����N�T�����|���A */
{
   stack_t ostk;
   printf("%s\n",str);
   if (sigaltstack(NULL, &ostk) < 0)
      perror(" sigaltstack exam fail.");
   if (ostk.ss_flags&SS_ONSTACK)
      printf("   flags=SS_ONSTACK \n");
   else if(ostk.ss_flags&SS_DISABLE)
      printf("   flags=SS_DISABLE \n");
   else 
      printf("   flags=%d\n",ostk.ss_flags);
   return;
}
void sig_segv(int signo)          	/* SIGSEGV�T������X */
{
    stack_t sigstk,ostk;
    check_ss_flags("in sig_segv:");
    printf("We catched SIGSEGV signal! \n");
    exit(0);
}
void sig_usr1(int signo)          	/* SIGUSR1�T������X */
{
    stack_t sigstk,ostk;
    check_ss_flags("in sig_usr1:");
    set_ss_stack(&sigstk, &ostk);     	/* �]�w���N�T�����|,�o�@���N���� */
    return;
}
int main(void)
{
    struct sigaction act;
    stack_t sigstk,ostk;
     /* �w�˰T������X�æb���N�T�����|�W���楦�� */
    act.sa_flags = 0;
    act.sa_flags |= SA_ONSTACK;         
    sigemptyset(&act.sa_mask);
    act.sa_handler = sig_segv;
    if (sigaction(SIGSEGV,&act,NULL) <0 )
   	   perror("SIGSEGV error");
    act.sa_handler = sig_usr1;
    if (sigaction(SIGUSR1,&act,NULL) < 0)
       perror("SIGUSR1 error");
    set_ss_stack(&sigstk, &ostk); 	/* �]�w���N�T�����| */
    check_ss_flags("before kill in main"); /* �˵����N�T�����| */
    kill(getpid(), SIGUSR1); 	/* ���ۤv�ǰeSIGUSR1�T�� */  
    check_ss_flags("after kill in main");         
    make_stack_overflow();	/* �y�����|�Ŷ����� */ 
    return;
}
