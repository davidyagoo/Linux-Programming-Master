#include "ch12.h"
#include "p12-8.c"   // socket_connect.c, �{��12-8
int main(int argc, char **argv)
{
    int connfd, n, result;
    char buf[256];
    connfd = socket_connect(NULL, "2003");    /* �P�A�ȫإ߳s�u */
    write(connfd, argv[1], sizeof(argv[1]));  /* �V�A�ȶǰe��� */
    n = read(connfd, buf, sizeof(buf));        /* Ū�A�Ȫ��^�e��� */
    buf[n] = 0;  /* �פ�� */
    printf("string from server = %s\n", buf);
    close(connfd);
    exit(0);
}
