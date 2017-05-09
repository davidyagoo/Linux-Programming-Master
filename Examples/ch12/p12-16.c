#include "ch12.h"
#include "p12-7.c"   //make_socket()

int main(int argc,char **argv)
{
   int listenfd, connfd, n;
   char buff[100];
   fd_set rset, xset;

   /* �ˬd�Ѽƨëإߺ�ť�M���r */
   if(argc != 2) {
      printf("Usage: a.out <port#>\n");
      exit(1);
   }
   listenfd = make_socket(SOCK_STREAM,atoi(argv[1]));
   listen(listenfd, 5);
   connfd = accept(listenfd, NULL, NULL);  /* �����s�u */
   /* �y�z�r���X�M�z */
   FD_ZERO(&rset);
   FD_ZERO(&xset);
   while(1){
      /* �Nconnfd�[�ܴN���M�ҥ~�y�z�r���X */
      FD_SET(connfd,&rset);
      FD_SET(connfd,&xset);
      /* ���ݴy�z�rconnfd�N���ΥX�{�ҥ~���� */  
      select(connfd+1, &rset, NULL, &xset, NULL);
      if(FD_ISSET(connfd, &xset)){ 
         n = recv(connfd,buff,sizeof(buff-1),MSG_OOB);
         if (n<0) err_exit("recv error");
         buff[n] = 0;
         printf("received %d OOB byte: %s\n",n,buff);
         FD_CLR(connfd,&xset);  
      }
      if(FD_ISSET(connfd, &rset)){ /* connfŪ�N�� */
         if((n = read(connfd, buff, sizeof(buff)-1)) == 0){
             printf("received EOF\n");
             exit(0);
         }
         buff[n] = 0;  /* �����פ�� */
         printf("read %d bytes: %s\n",n,buff);
         FD_CLR(connfd,&xset);  
      }
   }
}

