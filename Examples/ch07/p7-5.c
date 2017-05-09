#include "ch07.h"
volatile sig_atomic_t flag = 0;   /* �ӼЧӦb SIGALRM �T������X���Q�]�w. */
int main (void)
{
    sigset_t block_alarm;
    /* �_�l�T�����X */
    sigemptyset (&block_alarm);
    sigaddset (&block_alarm, SIGPROF);   /* �n���몺�T���OSIGALRM */
     ...
    while (1){
        sigprocmask (SIG_BLOCK, &block_alarm, NULL);    /* �]�w�T���̽� */
        if (flag){   /* �ˬd�T����F�_,�Y��F�h�M���Ч�flag  */         
            ACTIONS-IF-ARRIVED
            flag = 0;
        }
        sigprocmask (SIG_UNBLOCK, &block_alarm, NULL);  /* �Ѱ��T���̽� */   
        ...
    }
}

