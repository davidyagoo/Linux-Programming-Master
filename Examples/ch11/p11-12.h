#include "ch11.h" 
#include "p11-11.c"   //semaphore_P()/semaphore_V()
#include "p11-9.c"    // open_semaphore_set()

/* �����S���T���q���X */
#define rm_semaphore(sid) semctl(sid, 0, IPC_RMID,0)

struct exchange {
    char buf[BUFSIZ+80];    /* �ݥ洫�����*/
    int seq;                /* �Ȥ��J�����Ǹ� */
};

/* semun���c */
union semun {
   int val;
   struct semid_ds *buf;
   unsigned short *array;
};

key_t key1=123,key2=456;

/* �إ�/�}�Ҧ@���x�s�q�A�s�u����ϥΪ̦�}�Ŷ��A�Ǧ^���b�ϥΪ̪Ŷ�����} */
unsigned char *shminit(key_t key, int *shmid)
{
    unsigned char *retval;
    if((*shmid = shmget(key,sizeof(struct exchange),0666|IPC_CREAT))== -1)
        err_exit("shmget");
    if((retval = shmat(*shmid,(unsigned char *)0,0)) == (unsigned char *)-1 )
        err_exit("shmmat");
    return retval;
}

/* ���S���T���q���� */
void init_a_semaphore( int sid, int semnum, int initval)
{
    union semun semopts;    
    semopts.val = initval;
    semctl( sid, semnum, SETVAL, semopts);
}



