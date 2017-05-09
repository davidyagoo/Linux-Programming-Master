#include "ch08.h"
#define OUR_CLOCK CLOCK_REALTIME
timer_t mytimer;
void timer_intr(int signo, siginfo_t *extra, void *cruft) // �w�ɾ�����T������X
{
   int noverflow;
   if (signo==SIGINT) /* �ϥΪ̿�J��CRTL/C�T���A�פ�{������ */
      exit(1);  
   /* �˵��O�_���O�� */
   if (noverflow = timer_getoverrun(*(timer_t *)extra->si_value.sival_ptr))
      printf("timer has overflowerd--error\n");
   printf("timer expiration\n");
   return;
}
main(int argc, char **argv)
{
   int c;
   struct itimerspec i;
   struct timespec resolution;
   struct sigaction sa;
   sigset_t allsigs;
   struct sigevent timer_event;
   /* �����T�O�s�b�ҧƱ檺���� */
   if (clock_getres(OUR_CLOCK, &resolution)<0)
      err_exit("clock_getres");
   printf("Clock resolution %d sec %d nsec\n", 
             resolution.tv_sec, resolution.tv_nsec);
   /* �]�w�w�ɾ�����T�����|�Ҧ� */
   timer_event.sigev_notify=SIGEV_SIGNAL; /* ���ͰT�� */
   timer_event.sigev_signo=SIGRTMIN;       /* �n�ǰe���T�� */
   timer_event.sigev_value.sival_ptr=(void *)&mytimer; /* ��a�w�ɾ�ID���� */
   /* �إߩw�ɾ� */
   if (timer_create(OUR_CLOCK, &timer_event, &mytimer)<0) 
      err_exit("timer_create");
   /* �����w�ɾ�����T�� */
   sigemptyset(&sa.sa_mask);
   sigaddset(&sa.sa_mask,SIGRTMIN);  /* ����X��Ƥ��̽�SIGRTMIN�T�� */
   sa.sa_flags=SA_SIGINFO;             /* ��ɰT�� */
   sa.sa_sigaction=timer_intr;
   sigaction(SIGRTMIN, &sa, NULL);
   /* ����Ctr-c�T�� */
   sigaction(SIGINT, &sa, NULL);
   /* �T�w�w�ɮɶ��ó]�w�w�ɾ� */
   i.it_interval.tv_sec=0;
   i.it_interval.tv_nsec=resolution.tv_nsec*10; /* �w�ɶ��j�ɶ����ѪR�ת�10��*/
   i.it_value=i.it_interval;
   if (timer_settime(mytimer, 0, &i, NULL)<0)
      err_exit("timer_settime");
   sigemptyset(&allsigs);
   while(1){    /* �z�L��JCRTL/C�פ�{������ */
         sigsuspend(&allsigs);    // ���ݩw�ɾ�����T��
   }
}
