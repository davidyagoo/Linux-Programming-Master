#include "p11-12.h"

int main(void) /* �Ȥ�{�� */
{
    struct exchange *shm;
    int shmid, producer_ok,consumer_ok,i;

    /* �}�ҰT���qconsumer�Mproducer */
    consumer_ok = open_semaphore_set(key1, 1);
    //init_a_semaphore(consumer_ok, 0, 0);
    /* �إ߰T���qproducer */
    producer_ok = open_semaphore_set(key2, 1);
    //init_a_semaphore(producer_ok, 0, 0);

    /* ��o�ós�u�W��"shared"���@���x�s�q */
    shm = (struct exchange *)shminit(ftok("shared",0),&shmid);

    /* �q�@���x�s�qŪ�A�Ȱ�����Ҽg����ơA�ÿ�X����*/
    while(1){
       semaphore_P(producer_ok);   /* ���ݸ�Ʋ��ͧ��� */
       /* �B�z��ơA�J��"end"�����`�� */
       printf("%d recieived:Sequence=%d,data=%s",getpid(), shm->seq, shm->buf);
       if (strncmp(shm->buf, "end", 3) == 0)
          break;
       semaphore_V(consumer_ok);  /* ���A�Ȱ�������͸�� */        
    }
    /* �����@���x�s�q */
    shmdt(shm);
    semaphore_V(consumer_ok);  /* ���A�Ȱ�������͸�� */        
    exit(0);
}
