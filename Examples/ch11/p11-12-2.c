#include "p11-12.h"

int main(void) /* �A�ȵ{�� */
{
    struct exchange *shm;
    int producer_ok,consumer_ok,i;
    int shmid;
    char readbuf[BUFSIZ];

    /* �إ߰T���qconsumer�Mproducer */
    consumer_ok = open_semaphore_set(key1, 1);
    producer_ok= open_semaphore_set(key2, 1);
    init_a_semaphore(consumer_ok, 0, 1);  /* �T����O */
    init_a_semaphore(producer_ok, 0, 0);  /* �e�\�Ͳ� */

    /* ��o�ós�u�W��"shared"���@���x�s�q */
    shm = (struct exchange *)shminit(ftok("shared",0),&shmid);

    /* �q�Э��JŪ��ƨüg�ܦ@���x�s�q */
    for ( i=0; ; i++ ) {
         /* Ū�J��� */
        semaphore_P(consumer_ok);   /* ���ݫȤ���������@���x�s�q */
        printf("Enter some text:");
        fgets(readbuf,BUFSIZ,stdin);
         /* ��R�@���x�s�w�R */
        shm->seq = i;
        sprintf(shm->buf, "%s",readbuf);
        semaphore_V(producer_ok);  /* �e�\�Ȥ���������� */
        if (strncmp(readbuf, "end", 3) == 0 )
            break;
    }
    semaphore_P(consumer_ok); /* ���ݫȤ��������O���� */
    /* �����T���q */
    rm_semaphore(producer_ok);
    rm_semaphore(consumer_ok);

    /* �����ò����@���x�s�q */
    shmdt(shm);
    shmctl(shmid, IPC_RMID, (struct shmid_ds *)NULL);
    exit(0);
}
