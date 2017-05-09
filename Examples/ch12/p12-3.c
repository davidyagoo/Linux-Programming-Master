#include "ch12.h"
int main(void)
{
   int    stayopen = 1;
   struct servent *sp;
   setservent(stayopen);    /* �}�ҪA�ȸ�Ʈw�A�ǳƱ��y */
   while (1) {                /* �v�����y�n�O�� */
      sp = getservent();
      if (sp != (struct servent *)0)
         printf( "server name=%12s, port=%6d, proto=%4s\n", sp->s_name,
                   ntohs(sp->s_port), sp->s_proto);
      else
         break;
   }
   endservent();    /* �����A�ȸ�Ʈw */
   /* �M���˵�telnet�A�Ȫ��q�T�� */
   sp = getservbyname ("telnet", "tcp");
   if (sp != (struct servent *)0) 
      printf( "telnet's port is %d\n", ntohs (sp->s_port));
   else
      printf("ERROR: getservbyname call failed\n");
   return 0;
}
