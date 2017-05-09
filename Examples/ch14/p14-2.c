#include "ch14.h"
pthread_key_t key1, key2;
/* �ϥΰ�����M����ƪ��u�@��� */
void do_work(void)
{
   int num;
   char *vp;
   num = (int)pthread_getspecific(key1); /* ��o������M����ơA�o�O�@�ӱ`�q */
   vp = (char *)pthread_getspecific(key2);  /* ��o������M����ơA�o�O�@�ӫ��� */
   sprintf(vp,"\tThread %d is at work now, key2's value:%x ", num, vp);
}
/* ������}�l��ơA�t�d�]�w������M������䤧�� */
void start_func(int thread_num)
{
   char *buf, *vp;
   pthread_setspecific(key1, (void *)thread_num);
   buf = (char *)malloc(100);
   pthread_setspecific(key2, (void *)buf);
   do_work();
   vp = (char *)pthread_getspecific(key2);
   printf("Thread %d's thread specific data is :\n %s\n", thread_num, vp);
   if (thread_num !=0 ) // �_�l������Ǧ^�A�䥦������פ�
     pthread_exit(NULL);
}
/* ������M�������۳s���Ѻc��ơA�t�d�u�W�{�פ��������t���x�s�Ŷ� */
void destructor(void *value)
{
   free(value);
   printf("memory %x released by destructor\n",value);
}
int main(int argc,char *argv[])
{
   int rv;
   pthread_t tid;
   /* �إ߰�����M�������key1�Mkey2 */
   rv = pthread_key_create(&key1, NULL);
   check_error(rv, "Create key1");
   rv = pthread_key_create(&key2, destructor);
   check_error(rv, "Create key2");
   /* �إߤ@�Ӱ������star_func���u�@,�������s����1 */
   rv = pthread_create(&tid, NULL, (void *(*)())start_func, (void *)1);
   check_error(rv, "Thread create");
   /* �ۤv�]�ѻP�u�@�A�������s����0 */
   start_func(0);
   /* ���ݰ�����פ� */
   rv = pthread_join(tid, NULL);
   check_error(rv, "Thread join ");
   rv = pthread_key_delete(key1);
   check_error(rv, "key1 delete");
   pthread_exit(NULL);
}

