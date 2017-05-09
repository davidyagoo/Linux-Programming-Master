#include "ch14.h"
#define OUTPUTSCHEDPARAM(policy, priority)   printf(         \
                     "Thread %lx: Policy=%s, priority=%d\n", \
                     pthread_self(),                       \
                     (policy==SCHED_FIFO?"FIFO"            \
                       :(policy==SCHED_RR?"RR"             \
                       :(policy==SCHED_OTHER?"OTHER"       \
                       :"unknown"))), priority)
#include "p13-13.c"
#include "p14-6.c"

barrier_t barrier;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
 
void *t_routine(void *n)
{
   int rv, mypolicy, thread_no = (int)n;
   struct sched_param myparam;
   barrier_wait(&barrier);             // �]�浥���Ҧ��������F�A�{��13-13
   rv = pthread_mutex_lock(&mutex);   // �}�l�v�������ܼ� 
   check_error(rv, "mutex_lock");
   printf("Thread %d :",thread_no);
   /* �C�L�X����������������M�u���� */
   rv = pthread_getschedparam(pthread_self(),
                                   &mypolicy, &myparam);
   check_error(rv, "getschedparam");
   OUTPUTSCHEDPARAM(mypolicy, myparam.sched_priority);
   rv = pthread_mutex_unlock(&mutex);  // ���񤬥��ܼ�
   check_error(rv, "mutex_unlock");
}

int main(void)
{
   int rv, priority,  policy;
   struct sched_param param;
   struct sched_thread t_param;

   /* �_�l�Ƥ@��5������P�B���]�� */
   rv = barrier_init(&barrier, 5);    // �{��13-13 
   check_error(rv, "barrier_init");

   /* ��X�_�l����������������M�u���� */
   rv = pthread_getschedparam(pthread_self(), &policy, &param);
   check_error(rv,"main: getschedparam");
   OUTPUTSCHEDPARAM(policy, param.sched_priority);

   /*  �إ�4�Ӥ��P���������M�u���Ū������  */
   t_param.thread_func = t_routine;
   t_param.policy = SCHED_FIFO;
   t_param.num = 1;
   t_param.priority = sched_get_priority_min(SCHED_FIFO); 
   create_exlicit_sched_threads(&t_param); 

   t_param.num = 2;
   t_param.priority +=2;
   create_exlicit_sched_threads(&t_param);

   t_param.policy = SCHED_RR;
   t_param.num=3;
   t_param.priority = sched_get_priority_min(SCHED_RR);
   create_exlicit_sched_threads(&t_param);

   t_param.num=4;
   t_param.priority = sched_get_priority_max(SCHED_RR);
   create_exlicit_sched_threads(&t_param);

  /* ���ܦۤv�����������M�u���� */
   if (policy == SCHED_RR) {  // ���������O�ڭ̻ݭn�������A�u�����u����
      rv = pthread_setschedprio(pthread_self(),t_param.priority+6);
      check_error(rv, "getschedparam");
   } else {                       // �_�h���ܵ����M�u���� 
      param.sched_priority += 10;
      rv = pthread_setschedparam(pthread_self(),SCHED_RR, &param);
      check_error(rv, "getschedparam");
   }
   t_routine(0);     // �ѻP������v��
   pthread_exit((void *)NULL);
}

