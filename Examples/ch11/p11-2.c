#include "ch11.h"
int main(void)
{
    int pid, fd[2],len;
    char buffer[PIPE_BUF];
    FILE *stream; 
    if ( pipe(fd) != 0) 
        err_exit("pipe creation failed");
    if ((pid = fork())== 0) { /* �l����� */
        close(fd[1]);            /* ���ϥκ޽u���g�� */
        dup2(fd[0],0);           /* ����stdin,���s�ɦV�޽u����J�ݦ�stdin */
        close(fd[0]);            /* �����o�Ӥ��A���Ϊ��y�z�r */
        /* ��cat�L�o��X */
        if (execl("/bin/cat","cat", NULL/*"-n"*/, NULL) == -1)
            err_exit("Unable to run cat"); 
    } else {                      /* ������� */
        close(fd[0]);            /* ���ϥκ޽u����J�� */
        printf("you can type a line and the line will echoed:\n");
        dup2(fd[1],1);           /* ����stdout,���s�ɦV�޽u����X�ݦ�stdout */
        close(fd[1]);
        while (gets(buffer) != NULL)
           puts(buffer);         /* �g�ܺ޽u*/
    }
 } 
