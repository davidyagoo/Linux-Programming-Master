#include "ch11.h"
#define SHMSZ     27
int main(void)
{
    int shmid;
    key_t key;
    char *shm, *s;
    /* ��o�W����785�����@���x�s�q */
    key = 785; 
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) 
        err_exit("shmget");
    /* �s�u�Ӧ@���x�s�q */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
        err_exit("shmat");
    /* �q�@���x�s�qŪ�A�Ȱ�����Ҽg����ơA�ÿ�X����*/
    for (s = shm; *s != '\0'; s++)
        putchar(*s);
    putchar('\n');
    exit(0);
}
