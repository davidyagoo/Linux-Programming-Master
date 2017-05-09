#include "ch12.h"
#include "init_sockaddr.c"
int socket_connect(char *hostname, char *serv_port)
{
   int sockfd;
   struct sockaddr_in saddr;
   struct hostent *hp;
   char *host, myname[104];
   /* �_�l���A����IP��}�M�q�T�� */
   init_sockaddr(&saddr, hostname, serv_port); 
   /* �إ߮M���r */
   if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
      err_exit("socket error");
   /* �إ߻P�A�Ȫ��s�u */
   if(connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
      err_exit("connect error");
   return(sockfd);
}
