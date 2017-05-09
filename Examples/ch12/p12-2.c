#include "ch12.h"
int main(int argc, char *argv[])
{
   char *host, **names, **addrs, myname[256];
   struct hostent *hostinfo;
   /* �]�w�D�q�������O��ѼƯS���W�r�ε{������Ҧb�������W�r */
   if(argc > 1) 
  host = argv[1];
   else {
      gethostname(myname, 255);
      host = myname;
   }   
   hostinfo = gethostbyname(host);       /* ���o�D�q����}�T�� */
   if(!hostinfo) {
      fprintf(stderr, "cannot get info for host: %s\n", host);
      exit(1);
   }
   /* ���i���������W�M�O�W */
   printf("results for host %s:\n", host);
   printf("Official name: %s\n", hostinfo->h_name);
   printf("\t Aliases:");
   names = hostinfo->h_aliases;
   while(*names) {
      printf(" %s\n", *names);
      names++;
   }
    /* ���iIP��} */
   addrs = hostinfo->h_addr_list;
   while(*addrs) {
      printf("\taddress:%s\n",inet_ntoa(*(struct in_addr*)*addrs));
       addrs++;
   }
   exit(0);
}
