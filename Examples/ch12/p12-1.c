#include "ch12.h"
#define DATA1   "Fine,thanks."
#define DATA2   "Hello,how are you?"
int main(void)
{
    int sockets[2], child;
    char buf[1024];
    /* �إ߮M���r���� */
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0) 
        err_exit("socketpair error");
    /* �إߤl�����*/
    if ((child = fork()) == -1) 
        err_exit("fork error ");
    if (child != 0) {       /* �o�O������� */
        close(sockets[0]);  /* �����l��������M���r */
        /* Ū�Ӧۤl��������T�� */
        if (read(sockets[1], buf, sizeof(buf)) < 0) 
            err_exit("reading socket error");
        printf("parent %d received request: %s\n", getpid(), buf);
        /* �V�l������g�T�� */
        if (write(sockets[1], DATA1, sizeof(DATA1)) < 0) 
            err_exit("writing socket error");
        close(sockets[1]);    /* �q�T���� */
    } else {     /* �o�O�l����� */
        close(sockets[1]);     /* ��������������M���r�� */
        /* �ǰe�T����������� */
        if (write(sockets[0], DATA2, sizeof(DATA2)) < 0) 
            err_exit("writing socket error");
        /* Ū�Ӧۤ���������T�� */
        if (read(sockets[0], buf, sizeof(buf)) < 0)
            err_exit("reading socket error");
        printf("child process %d received answer: %s\n", getpid(),buf);
        close(sockets[0]);     /* �q�T���� */
    }
}
