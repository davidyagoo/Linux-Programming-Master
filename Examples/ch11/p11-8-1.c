#include "ch11.h"
#define SHMSZ     27
int main(void)
{
    char c, *shm, *s;
    int shmid;
    /* �إߦW��"785"���@���x�s�q */
    if ((shmid = shmget(785, SHMSZ, IPC_CREAT|0666)) < 0) 
        err_exit("shmget");
    /* �s�u�@���x�s�q�ܰ��������ƪŶ� */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
        err_exit("shmat");
    /* �g�@��r���ܦ@���x�s���t�@�Ӱ���� */
    s = shm;
    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = '\0';
    exit(0);
}
