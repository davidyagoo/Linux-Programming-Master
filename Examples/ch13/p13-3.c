#include "ch13.h"
#define SIZE 10
int a[SIZE],b[SIZE];

void max_fun(int *arg)    /* �D�}�C�̤j�����A�O�����m�Ǧ^ */
{
   int * ap=arg;
   int rv, i, k;
   k=0;
   for (i=1; i<SIZE; i++){
      if (ap[i] > ap[k]) 
         k= i;
   }
   pthread_exit((void *)&ap[k]);   // ���浲�G     
}

int main(void)
{
   pthread_t tid1,tid2;    // ������лx
   int i, rv, **ptr1, **ptr2;
   
   for (i=1; i<SIZE; i++){ // ���Ͱ}�C���������
      a[i]=rand();
      b[i]=rand();
   }
   /* �إ�2�Ӱ����������max_fun()���O�B�z�}�Ca�Mb */
   rv = pthread_create(&tid1, NULL, (void*(*)())max_fun, a);
   check_error(rv, "pthread_create: tid1");
   rv = pthread_create(&tid2, NULL, (void*(*)())max_fun, b);
   check_error(rv, "pthread_create: tid2");
   /* ����2�Ӱ�������� */
   pthread_join(tid1, (void **)&ptr1);
   pthread_join(tid2, (void **)&ptr2);
   printf ("thread1's max value is: %d\n", *ptr1);
   printf ("thread2's max value is: %d\n", *ptr2);
   printf ("max value = %d\n", (*ptr1)>(*ptr2)? (*ptr1):(*ptr2));
   exit(0);
}
