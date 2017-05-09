#include "ch13.h"
#include <sys/shm.h>
#include "xmalloc.c"
/* �إߤ@�ӰʺA���t�Ŷ��B�㦳�w���ݩʪ������ܼ� */
pthread_mutex_t *mutex_customized (int shared, int type, int key)
{
   int rv;
   key_t shmid;
   pthread_mutex_t *mtx;
   pthread_mutexattr_t mtxattr;  // �����ܼ��ݩʪ���
   /* �_�l�Ƥ����ܼ��ݩʪ��� */
   rv = pthread_mutexattr_init (&mtxattr);
   check_error(rv, "mutexattr_init ");
   /* �]�w�@���ݩ� */
   rv = pthread_mutexattr_setpshared(&mtxattr, shared);
   check_error(rv, " mutexattr_setpshared ");
   /* �]�w���A�ݩʡA�b�����t�ΤW�ݭn���T�w�q�S�����ե���_GNU_SOUCE */
   rv = pthread_mutexattr_settype (&mtxattr, type);
   check_error(rv, "mutexattr_settype");
   /* �������ܼƤ��t�@���x�s�Ŷ� */
   if (shared == PTHREAD_PROCESS_PRIVATE)
      mtx = (pthread_mutex_t *)xmalloc(sizeof(pthread_mutex_t));     
   else {  // ������@�ɤ����ܼƤ��t�b�@���x�s��
      shmid = shmget(key, sizeof(pthread_mutex_t), 0666|IPC_CREAT);
      if (shmid == -1) 
          err_exit("shmget error");
      mtx = (pthread_mutex_t *)shmat(shmid, (char *)0, 0);
      if ((int)mtx == -1) 
         err_exit("shmget error");
   }
   /* ���ݩʪ���_�l��mtx */
   rv = pthread_mutex_init(mtx, &mtxattr);
   check_error(rv, "mutex_init ");
   /* �ߧY�P�����A�ݭn���ݩʪ��� */
   rv=pthread_mutexattr_destroy(&mtxattr);
   check_error(rv, "mutexattr destroy ");
   return (mtx);
} 
#define KEY 8125
pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;  // �R�A�_�l�ƪ�������p�������ܼ�
pthread_mutex_t mtx2;       // �ʺA�_�l�ƪ�������p�������ܼ�
pthread_mutex_t *mtx3;      // ������@�ɤ����ܼ�
int main(void)
{
   int rv;
   // ...
   rv = pthread_mutex_init (&mtx2, NULL); // �_�l��mtx2���t�ιw�]�����ܼ�
   /*�_�l��mtx3���w�������@�ɻ��k�����ܼ�*/
   mtx3 = mutex_customized(PTHREAD_PROCESS_SHARED,
                            PTHREAD_MUTEX_RECURSIVE,KEY);
   // ...�M�ε{�����䥦�{���X
   /* �P��mtx2 */
   rv = pthread_mutex_destroy(&mtx2);
   check_error(rv, "mutex_destroy: mtx2");
   pthread_exit(NULL);
}
