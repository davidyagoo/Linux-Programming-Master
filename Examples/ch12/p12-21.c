#include "ch12.h"
#include "p12-6.c"   //init_sockaddr()
#define MAXMSG 512
int main(int argc, char **argv) 
{ 
   ...
   /* �]�w�M���r�����O�ɿﶵ */
   timev.tv_sec = 5;
   timev.tv_usec = 0;
   setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timev, sizeof(timev));
   while(1){
      ...
       /* ��������ܪA�ȶǦ^���^��,�Y�O�ɩΥX���A�פ���� */
      if ((n = recvfrom(sock,rcvmsg, MAXMSG,0,NULL,NULL)) < 0){
         if(errno == EWOULDBLOCK) 
            fprintf(stderr,��socket timeout\n��);
         err_exit("(client) receive error ");         
      }
      rcvmsg[n] = 0;
      printf(��client received message: %s��,rcvmsg);
   }
   ...
}

