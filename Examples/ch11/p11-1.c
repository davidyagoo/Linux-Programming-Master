#include "ch11.h"
int main (void)
{
    pid_t pid;
    int n, mypipe[2];
    char buffer[BUFSIZ+1], some_data[] = "Hello, world!";
    /* �إߺ޽u */
    if (pipe (mypipe)) 
        err_exit("Pipe failed.\n");
    /* �l�ͤl����� */ 
    if ((pid = fork())==(pid_t)0) { /* �o�O�l����� */
        close(mypipe[1]);     /* �l����������޽u��X�� */
        n = read(mypipe[0], buffer, BUFSIZ);
        printf("child %d: read %d bytes: %s\n",getpid(),n,buffer);
    } else {   /* �o�O������� */
        close(mypipe[0]);    /* ������������޽u��J�� */
        n = write(mypipe[1], some_data, strlen(some_data));
        printf("parent %d: write %d bytes: %s\n", getpid(), n, some_data);
    }
    exit (EXIT_SUCCESS);
}
