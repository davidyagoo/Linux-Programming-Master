#include "ch10.h"

int input_timeout(int filedes, unsigned int seconds)
{
    fd_set set;
    struct timeval timeout;
    int n;
    char buf[1024];

    FD_ZERO(&set);             /* �_�l�ɮ״y�z�r���X */
    FD_SET(filedes, &set);
    timeout.tv_sec = seconds;  /* �_�ltimeout��Ƶ��c */
    timeout.tv_usec = 0;

    /* select�ɶ�����Ǧ^0�F��J�N���Ǧ^1�F�X�{���~�Ǧ^-1 */
again:
    if ((n = select(FD_SETSIZE, &set, NULL, NULL, &timeout)) < 0) { //�X�{���~
        if (errno = EINTR) 
            goto again;
    }
    else if (n > 0) {   //��J�N��
        n = read(filedes,buf,sizeof(buf));
        printf("read data:  %s\n",buf);
    }
    else  //�ɶ����
        printf("tiomeout for select\n");
    return n;
}

int main (void)
{
    fprintf(stderr, "select returned %d.\n",input_timeout(STDIN_FILENO, 5));
    return 0;
}
