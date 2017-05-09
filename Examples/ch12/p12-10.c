#include "ch12.h"
#define LISTENQ  5
int socket_listen(int type, int server_port)
{
   int sockfd;
   struct sockaddr_in name;
    /* �إ߮M���r */
   if ((sockfd = socket(AF_INET, type, 0)) < 0)
      err_exit("socket error");
   /* �_�l�M���r��}���c */ 
   bzero (&name,sizeof(name));
   name.sin_family = AF_INET;
   name.sin_addr.s_addr = htonl(INADDR_ANY);
   name.sin_port = htons(server_port);
   if (bind(sockfd, (struct sockaddr *)&name, (socklen_t)sizeof(name)) < 0)
      err_exit ("bind");
   /* �إߺ�ť��C */
   listen(sockfd, LISTENQ);
   return sockfd;
}
