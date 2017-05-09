#include "ch12.h"
#include "p12-7.c"   // make_socket()
#define MAXMSG  1024

int main(void)
{
   int sock,size,nbytes;
   struct sockaddr_in name;
   char message[MAXMSG];

   /* �إ߸�Ƴ��M���r */
   sock = make_socket(SOCK_DGRAM, 0);

   /* �d�X�æC�L�t�νᵹ���q�T��� */
   size = sizeof(name);
   if (getsockname(sock, (struct sockaddr *)&name, (socklen_t *)&size)) 
      err_exit("getting socket name");
   printf("Socket has port #%d\n", ntohs(name.sin_port));

   while(1){
      /* �q�M���rŪ��� */
      size = sizeof(name);
      nbytes = recvfrom(sock, message, MAXMSG, 0,
                  (struct sockaddr *)&name, (socklen_t *)&size);
      if (nbytes < 0)
         err_exit("recfrom (server)");
      /* �C�L�X���쪺�T�� */
      printf("Server got message: %s\n", message);
      /* �N�T���Ǧ^���ǰe�� */
      nbytes = sendto(sock, message, nbytes, 0,(struct sockaddr *)&name, size);
      if (nbytes < 0)
         err_exit("sendto(server)");
   }
}
