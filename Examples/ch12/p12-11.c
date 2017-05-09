#include "ch12.h"
#include "p12-7.c"  // make_socket()
#define LISTENQ  5
#define MAXLINE  512
int main(int argc, char **argv)
{
   int listenfd,connfd;
   socklen_t len;
   struct sockaddr_in servaddr,cliaddr;
   char buff[MAXLINE];
   time_t ticks;
   /* �إߨéR�W�M���A5013���A�ȳq�T�� */
   listenfd = make_socket(SOCK_STREAM, 5013);  
   listen(listenfd, LISTENQ);    /* �إߺ�ť��C */
   /* �s�u�B�z */
   for(; ;){
     len = sizeof(cliaddr);
      /* �����s�u */
     connfd=accept(listenfd, (struct sockaddr *)&cliaddr, &len);
      /* �C�L�X�s�u�Ȥ᪺IP��} */
     printf("connect from %s,port %d\n", 
                    inet_ntoa((struct in_addr)cliaddr.sin_addr),
                    ntohs(cliaddr.sin_port));
      /* �V�Ȥ���i�ɶ� */
     ticks = time(NULL);
     sprintf(buff,"%.24s\r\n",ctime(&ticks));
     write(connfd,buff,strlen(buff));
     close(connfd);        /* �����s�u�M���r */
   }
}
