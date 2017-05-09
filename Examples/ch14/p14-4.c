#include "ch14.h"
int count;
int i=-1;             // �����I�Ч�
volatile int val=0;   // volatile�׹��H���sĶ���復�i��ﵽ

void *thread_routine(void *arg)   // ������}�l��� 
{
   int state = PTHREAD_CANCEL_DISABLE;
   int oldstate, j;
   for (count=1;;count++) {
      for(j=0;j<1000;j++)   // ����u�@
         val=(val*j)/count;
      if (count%1024 ==0){
         i=1;
         pthread_testcancel(); // // �C�j2048�ӭ��N�^���@�������ШD
      } else if ((count-100)%2048 == 0) {
         /* �i�J���i�����u�@�� */
         pthread_setcancelstate(state, &oldstate); // ���e�\�Q����
         for(j=0;j<1000000;j++)
            val=(val*j)/count;
         pthread_setcancelstate(oldstate, &state);  // �٭�H�e���i�������A
         i=0;      
         pthread_testcancel(); // ����ήɦ^���i��X�{���a�������ШD
      } 
   }
}
int main(void)
{
   pthread_t tid;
   int rv;
   void * result;
   rv=pthread_create(&tid, NULL, thread_routine, NULL);
   check_error(rv,"Create thread");
   sleep(3);
   rv=pthread_cancel(tid);              // �V������o�X�����ШD
   check_error(rv, "cancel thread");
   rv=pthread_join(tid, &result);
   if (result == PTHREAD_CANCELED)
      printf("thread %lx was canceled at itertion %d,i=%d\n", tid,count,i);
   else 
      printf("Thread %lx was not canceled. count=%d,i=%d\n",tid, count, i);
   return 0;
}
