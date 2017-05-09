#include "ch14.h"
typedef struct Sema{  
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int count; 
} sema_t;    //�T���q��Ƶ��c
sema_t semaphore = { PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, 1};
#define THREADS 4

void cleanup_mutex(void *arg)  //�����ܼƸ���/�M�z���
{
    printf("\tthread %lx: cleanup/unlock_mutex\n", pthread_self());
    pthread_mutex_unlock((pthread_mutex_t *)arg);
}

void AquireSemaphore(sema_t *ps)
{
    pthread_mutex_lock(&ps->lock);
    pthread_cleanup_push(cleanup_mutex, &ps->lock); //�إߤ����ܼƲM�z��
    while (ps->count == 0)
        pthread_cond_wait(&(ps->cond), &(ps->lock));
    --ps->count; 
    pthread_cleanup_pop(1);   // ���񤬥��ܼ�
}

void ReleaseSemaphore(sema_t *ps)
{
   pthread_mutex_lock(&ps->lock);
   ++ps->count;
   pthread_cond_signal(&ps->cond);
   pthread_mutex_unlock(&ps->lock);
}

void cleanup_sema(void *arg)   // �T���q�M�z��
{
   printf("\tthread %lx: cleanup_sema\n",pthread_self());
   ReleaseSemaphore((sema_t *)arg);
}

void * thread_routine(void * arg)  // ������}�l���
{
   int rv;
   AquireSemaphore(&semaphore);    // ��o�T���q
   pthread_cleanup_push(cleanup_sema, &semaphore);   // �إ߰T���q�M�z��
   printf ("   thread %lx: sleep\n", pthread_self());
   sleep(1);
   printf ("   thread %lx: waken from sleep\n", pthread_self());
   pthread_cleanup_pop(0);        // �X�{�T���q�M�z�� 
   ReleaseSemaphore(&semaphore);  // ����T���q
}

int main(int argc, char* argv[])
{
   pthread_t thread_id[THREADS];
   int i, rv, *status;

   for (i=0; i<THREADS; i++) {  // �إ߳\�h�Ӱ����
      rv = pthread_create (&thread_id[i], NULL, thread_routine, NULL);
      check_error(rv, "Create thread");
   }
   sleep (2);
   for (i=0; i<THREADS; i++) { // �ίv2���A��������
      if ((rv = pthread_cancel (thread_id[i]))== ESRCH) // ������i��w�g�פ�
         printf("thread %lx dose not exist\n", thread_id[i]);
      rv = pthread_join(thread_id[i], (void **)&status);
      check_error(rv, "Join thread");
      if (status==PTHREAD_CANCELED)  // �˵��פ��]
         printf("thread %d canceled %lx\n", i, thread_id[i]);
      else 
         printf("thread %d was not canceled\n", i);
   }
   return 0;
}
