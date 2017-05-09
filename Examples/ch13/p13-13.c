#include "ch13.h"
typedef struct barrier_struct {  //barrier��Ƶ��c
   int             valid;           //�X�k�_�l�ƼЧ�
   pthread_cond_t   cv;             //�����ܼ�
   pthread_mutex_t  mtx;            //�۳s�������ܼ�
   int   predicate;                 //����z��,�ۦP���]��P�B�I�㦳�ۦP����
   int   barrier_val;               //�n���ݪ�������Ӽ�
   int   blocked_threads;           //�w��F��������Ӽ�
} barrier_t;                             
/* �Ω�O�@barrier�_�l�ƪ������ܼ� */
pthread_mutex_t barrier_init_mutex = PTHREAD_MUTEX_INITIALIZER;
#define BARRIER_VALID 546731      //barrier�_�l�ƼЧ�
/* barrier b�_�l�ƨ�� */
int barrier_init(barrier_t *b, int val)
{
   int rv;
   /* �ӽ�barrier_init_mutex,�ϱo�C���u�e�\�@�Ӱ�����i��_�l�� */
   if ((rv=pthread_mutex_lock(&barrier_init_mutex))!=0) 
      return (rv);   //�W��X��
   if (b->valid == BARRIER_VALID) { // �w�i��L�_�l�ơA���������s�_�l��
      /* ��o�Ω�]��M�����ܼƪ������ܼ� */
      if ((rv=pthread_mutex_lock(&b->mtx))!=0){ 
         pthread_mutex_unlock(&barrier_init_mutex); 
         return(rv);
      }
      if (b->blocked_threads !=0 ){// ��barrier�٦��ݵ��ݪ�������A�Ǧ^���~
         pthread_mutex_unlock(&b->mtx);
         pthread_mutex_unlock(&barrier_init_mutex);
         return(EBUSY);
      }
      /* ���]barrier�p�ƭȫ�Ǧ^ */
      b->barrier_val=val;
      if ((rv=pthread_mutex_unlock(&b->mtx))!=0) {
         pthread_mutex_unlock(&barrier_init_mutex);
         return(rv);
      }
   }else {  // �Ĥ@���_�l��
      if ((rv=pthread_mutex_init(&b->mtx, NULL))!=0)
         return (rv); 
      if ((rv=pthread_cond_init(&b->cv, NULL)) !=0) {
         pthread_mutex_unlock(&barrier_init_mutex);
         return (rv);
      }
      b->barrier_val=val;
      b->blocked_threads =0;
      b->predicate =0;
      b->valid = BARRIER_VALID;
   }
   if ((rv=pthread_mutex_unlock(&barrier_init_mutex))!=0) // ������A�M��Ǧ^
      return (rv);
   return (0);
}  
  
/* �]�浥�ݨ�� */
int barrier_wait(barrier_t *b)
{
   int rv, predicate;
   if (b->valid != BARRIER_VALID) // �ˬd�]�檺�X�k��
      return(EINVAL);             // �]�楼�_�l�ƿ��~
   if ((rv=pthread_mutex_lock(&b->mtx)) != 0) //�ӽХΩ�]��M�����ܼƪ������ܼ�
      return (rv);     // �W��X��
   predicate = b->predicate;  // �x�s�����P�B�z����
   b->blocked_threads++;       // �W�[��F������p��
   if (b->blocked_threads == b->barrier_val) {  // �o�O�̫��F�������
      /* ���U���P�B���]�]��� */
      b->predicate += 1;                     
      b->blocked_threads = 0; 
      /* ����Ҧ������������ */
      if ((rv=pthread_cond_broadcast(&b->cv))!= 0) { 
          pthread_mutex_unlock(&b->mtx); // �s���X��,���񤬥��ܼƫ�Ǧ^
          return(rv);  
      }
   }else{              // �o�O����F�������
      /* ���ݡA����Ҧ���������w��F */
      while (b->predicate == predicate){
         rv = pthread_cond_wait(&b->cv, &b->mtx);
         if ((rv!=0)&&(rv!=EINTR)){
            pthread_mutex_unlock(&b->mtx);
            return(rv);  // ���󵥫ݥX��,���񤬥��ܼƫ�Ǧ^
         }
      }
   }
   /* �]��P�B�����A����Ω�]��M�����ܼƪ������ܼ� */
   if ((rv=pthread_mutex_unlock(&b->mtx))!=0)
      return(rv);   // ������X��
   return(0);  // �зǶǦ^
}
