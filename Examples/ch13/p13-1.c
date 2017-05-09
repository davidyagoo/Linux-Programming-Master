#include "ch13.h"
#define NUM_THREADS 4 
#define VECL 4*10000000
double a[VECL], b[VECL], sum;
struct args {         // dotsum�ϥΪ����
   pthread_t tid;       // �����ID
   int l_sum;           // �����I�n
   int index;               // �q0�}�l��������s��
} tharg[NUM_THREADS];     // �C�Ӱ���������@�Ӥ���
void *dotsum(void *arg)   // �D�����I�n��������}�l���
{
   struct args *ap = (struct args *)arg;
   int  i, start, end;
   double l_sum = 0.0;                           // �����I�n
   start = ap->index * (VECL/NUM_THREADS);   // �V�q�}�l�I 
   end   = start + (VECL/NUM_THREADS);        // �V�q�����I 
   printf("thread %i do from index %d to %d\n",ap->index, start,end-1);
   for (i = start; i < end; i++) 
      l_sum += (a[i]*b[i]);
   ap->l_sum = l_sum;                           // �x�s�p�⵲�G 
   return;
}
int main(void)
{
   int  i;
   assert(VECL%4==0);                  // �u������������{���~���T 
   for (i=0; i<VECL; i++)
      a[i]=b[i]=1.0;
   for(i=1; i<NUM_THREADS; i++) {  // �إ�NUM_THREADS-1�Ӱ�����������dotsum()��� 
      tharg[i].index = i;
      pthread_create(&tharg[i].tid, NULL, dotsum, (void *)&tharg[i]);
   }
   tharg[0].index = 0;
   dotsum((void *)&tharg[0]);      /* �D�b�{�ѻP�p�� */
   for(i=1; i<NUM_THREADS; i++)   /* ���ݨ䥦����������p�� */
      pthread_join(tharg[i].tid, (void **)NULL);
   /* �֥[�C�Ӱ�����������M�ÿ�X���G */
   sum=0.0;
   for (i=0; i<NUM_THREADS; i++)
      sum += tharg[i].l_sum;
   printf ("Sum =  %lf \n", sum);
   pthread_exit(NULL);
}
