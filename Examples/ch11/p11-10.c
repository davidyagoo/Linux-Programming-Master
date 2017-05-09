#include "ch11.h"
union semun {  /* ����semun���c */
   int val;
   struct semid_ds *buf;
   unsigned short *array;
};
/* �����S���T���q���X */
#define rm_semaphore(sid) semctl(sid, 0, IPC_RMID,0)
/* ���S���T���q���� */
void init_a_semaphore( int sid, int semnum, int initval)
{
   union semun semopts;    
   semopts.val = initval;
   semctl( sid, semnum, SETVAL, semopts);
}
/* ���S���T���q���X���� */
void init_all_semaphore( int sid, int val_array[])
{
   union semun semopts; 
   semopts.array = val_array;
   semctl( sid, 0, SETALL, semopts);
}
/* ���ܰT���q���X���s���v��,�v���Ѽƥ����O�Φp"660"���r�� */
int changemode(int sid, char *mode)
{
   int rc;
   union semun semopts;    
   struct semid_ds mysemds;
   semopts.buf = &mysemds;    /* ��semopts.buf ���V�ڭ̦ۤv�w�q���w�R�� */
   /* ��o���w��Ƶ��c���ثe�� */
   if ((rc = semctl(sid, 0, IPC_STAT, semopts)) == -1)
      return -1;
   sscanf(mode, "%o", &semopts.buf->sem_perm.mode); /* ���ܦs���v�� */
   /* ��s���w��Ƶ��c */
   return(semctl(sid, 0, IPC_SET, semopts));
}
