#include "ch12.h"
#include "p12-8.c"  //socket_connect()

int main(int argc,char **argv)  /* ������O�G <�{���W> <�D�q���W> <�q�T��>  */
{
   int sockfd;
   char buf[100];

   if(argc != 3) { 
     printf("Usage: a.out <host> <port#>\n");
     exit(1);
   }
   sockfd = socket_connect(argv[1],argv[2]);
   write(sockfd,"--abcdefghijklmnopqrstuvwxyz--",30);
   printf("wrote 30 bytes of normal data\n");
   send(sockfd,"#",1,MSG_OOB);    /* �ǰe�@���W�~��� */
   printf("wrote 1 byte of OOB data\n");
   write(sockfd,"=====1234567890=====", 20);
   printf("wrote 20 bytes of normal data\n");
   send(sockfd,"!",1,MSG_OOB);   /* �ǰe�@���W�~��� */
   printf("wrote 1 byte of OOB data\n");
   write(sockfd,"END",3);
   printf("wrote 3 byte of normal data\n");
   exit(0);
}
