#include "ch13.h"
#include "err_exit.h"
struct alarmtag {
   time_t    the_time;              // SIGALRM�T�������ɶ�
   int       got_alarm;             // SIGALRM�T�������Ч�
} alarmtime;
void *signal_thread(void *);     // �M���B�z�{���פ�T���������
void *work_thread(void *);       // �u�@�����
void alarm_handler(int signal)  // SIGALRM�T���������
{
//   printf("catch ALARM ,%d\n",pthread_self());
   time (&alarmtime.the_time);        /* ���ثe��l�ɶ�  */
   alarmtime.got_alarm = 1;            /* �]�w�T����ή�� */
}

int main (int argc, char *argv[])
{
   pthread_t  sig_tid, work_tid;     
   int rv; 
   sigset_t sig_set;
   struct sigaction sa;
   /* �]�wSIGALRM�T�����ʧ@ */
   sa.sa_handler = alarm_handler;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART; 
   if (sigaction(SIGALRM, &sa, NULL) == -1)   
      err_exit("sigaction failed");             // �T���ʧ@�]�w�X�� 
   /* �̽��Ҧ��T���A���tSIGALRM,SIGINT */
   pthread_sigmask(SIG_SETMASK, NULL, &sig_set);
   sigaddset(&sig_set, SIGINT);
   sigaddset(&sig_set, SIGUSR1); 
   rv = pthread_sigmask (SIG_BLOCK, &sig_set, NULL);
   check_error(rv, "pthread_sigmask");
   /* �إ߰T���B�z������A���~�ӳ]�w���T���̽� */
   rv = pthread_create (&sig_tid, NULL, signal_thread, NULL);
   check_error(rv, "pthread_create");
   /* �ܧ�T���̽��A��}SIGALRM�T�� */
   sigemptyset(&sig_set);
   sigaddset (&sig_set, SIGALRM);
   rv = pthread_sigmask (SIG_UNBLOCK, &sig_set, NULL);
   check_error(rv, "pthread_sigmask");
   /* �إߤu�@������A���~�ӷs�]�w���T���̽� */
   rv = pthread_create (&work_tid, NULL, work_thread, NULL);
   check_error(rv, "pthread_create");
   /* ���ݰ�����פ� */
   rv = pthread_join(work_tid, NULL);
   check_error(rv, "pthread_join");
   rv = pthread_kill(sig_tid, SIGUSR1);
   rv = pthread_join(sig_tid, NULL);
   check_error(rv, "pthread_join");
   printf("Good Bye\n");
   exit(0);
}

void *work_thread(void *arg)  /* �u�@����� */
{
   int i=0;
   alarmtime.got_alarm=0;
   printf("Work_thread: I am runing, my tid is: %lu\n",pthread_self());
   alarm(5);                         // �]�w�@���w�ɡA�o�O�ǰe����������T��
   printf("Work_thread: I set a alarm and go to sleep now.\n zzz~~~\n");
   while (!alarmtime.got_alarm);   // ���檽��Q�x�饴�_
//      for (i=0;i<10000000;i++)
//         for(j=0;j<100000;j++)
//           ;   // �C�j2000�ӭ��N��X�@�q�T��
//         printf(" ~~~zzz ");
//   }
   printf("Work_thread:The alam waken me up at %s", ctime(&alarmtime.the_time));
   printf("Work_thread:I finished.\n");
   pthread_exit(NULL);
}
void *signal_thread (void *arg)   /* �M���B�z�T��������� */
{
   int   sig, rv;
   sigset_t   wait_set, sig_set;   
   printf("Signal_thread:I am running, my tid is %lu\n", pthread_self());    
   /* ���ݯS���T�� */
   sigemptyset(&wait_set);
   sigaddset (&wait_set, SIGUSR1);  
   sigaddset (&wait_set, SIGINT);  
   rv = sigwait (&wait_set, &sig);
   check_error(rv, "sigwait");
   switch (sig) {
   case SIGINT:     /* �B�z SIGTERM  */
      // ...  �������e���M���B�z�{���X
      /* ��}�T���̽��A�åH�w�]�ʧ@�A�����͸ӰT���Ϧۤv�פ�A�i�@�B�ɭP������פ�. */
      printf ("Signal_thread:I received SIGINT:%d\n", sig);
      sigemptyset(&sig_set);
      sigaddset (&sig_set, sig); 
      rv = pthread_sigmask(SIG_UNBLOCK, &sig_set, NULL);
      signal(sig, SIG_DFL);   // �{��7-3
      raise (sig);              // �ǰe���ۤv���P�B�T��
      pthread_exit(NULL);      // �����|����
   case SIGUSR1:
      printf ("Signal_thread:I received SIGUSR1 and finished.\n");
      pthread_exit(NULL); 
   default:         /* �䥦�T���A������X�{ */
      fprintf (stderr, "Unexpected signal %d ", sig);
      exit(0); 
   }
}
