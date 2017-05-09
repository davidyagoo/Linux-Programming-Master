#include "ch12.h"
#include "p12-7.c"   // make_socket.c", �{��12-7
void doit(int);
int main(void)
{
   int server_sockfd, client_sockfd;
   int server_len, client_len;
   struct sockaddr_in client_address;
   server_sockfd = make_socket(SOCK_STREAM, 2003);
   /* �إ߳s�u��C�A�����l������פ�T�� */
   listen(server_sockfd, 5);
   signal(SIGCHLD, SIG_IGN);
   while(1) {
      printf("server waiting\n");
      /* �����s�u */
      client_len = sizeof(client_address);
      client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_len);
      /* ���o�ӫȤ�إߤ@�Ӥl����� */
       if(fork() == 0) {             /* �Y���l������A�����æ^���Ȥ᪺�T�� */
         close(server_sockfd);      /* �l�����������ť�M���r */
         doit(client_sockfd);       /* �B�z�Ȥ᪺�ШD */
         close(client_sockfd);      /* �B�z���������M���r */
         exit(0);                     /* �l������פ� */
      } else {
         close(client_sockfd);     /* ������������Q�s�u���M���r */
      }
   }
}
void doit(client_sockfd)
{
   char buf[255];
   int n;
   /* �����æ^���Ȥ᪺�T�� */
   n = read(client_sockfd, buf, sizeof(buf));
   buf[n] = 0;
   sleep(1);
   write(client_sockfd, buf, n);
}
