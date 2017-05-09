#include "filelock.h"
int main(void)
{
    int fd;
    off_t fdpos;
    if((fd = open("tempfile", O_RDWR|O_CREAT, 0666)) < 0)    /* �}���ɮ� */
       err_exit("open error");
    /* ���ɮק��Ψ�᪺�X�R�����m�g�� */
    if (SET_LOCK(fd, F_WRLCK, 0, SEEK_END, 0) == -1) 
       printf("%d set write lock failed\n", getpid());
    else
       printf("%d set write lock success\n", getpid());
    /* �w���ɮצ�m��ثe�ɮק��A�üg�J8�Ӧr�� */
    fdpos = lseek(fd, 0L, SEEK_END);
    write(fd, "8 bytes.", 8);   
    /* ��������e���]�w���g��A����ڨå�����A�]���ɮק�����m�w�Ჾ */
    if (un_lock(fd, 0L, SEEK_END, 0) == -1) 
       err_exit("UN_LOCK error")
    else
       printf("%d un_lock(fd,0,SEEK_END,0) success\n", getpid());
    /* ���l������b�Ӱϰ�]�wŪ�����Ҥ�������O�_�w���T�����g�� */
    if (vfork()== 0){   /* �l����� */
        /* �����ɮ׸m�g��A����]�w��������������ϰ쥼���� */
       if (SET_LOCK(fd, F_WRLCK, 0, SEEK_SET, 0) == -1)
          printf("%d: there are some locks on the file\n",getpid());
       else
          printf("%d: no any locks on the file\n",getpid());
       exit(EXIT_SUCCESS);
    }
    /* ������� */
    sleep(5);       /* �T�O������������} */
    exit(EXIT_SUCCESS);
}
