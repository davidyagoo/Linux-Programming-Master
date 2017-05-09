#include "p11-7.h"
int main(void)
{
   int running = 1, msgid;    
   struct my_msg msgbuf;
   long int msg_type = -57;    /* �u���������A�p��57���T�� */
   /* �إ�/�}�ҰT����C */
   if ((msgid = msgget((key_t)1234, 0666|IPC_CREAT)) == -1) 
      err_exit("msgget failed");
   /* �q��C���ϴ_�����T���A���즬��r�ꡨend�� */
   while(running) {/* �u���������A�p��57���T��,������ */
      if (msgrcv(msgid, (void *)&msgbuf, BUFSIZ, -57, IPC_NOWAIT)!= -1)
         printf("You wrote: %s", msgbuf.text);        /* ��ܦ��쪺�T�� */
      else if (errno==ENOMSG /* ���зǶ��Ǳ����T�� */
                && msgrcv(msgid, (void *)&msgbuf, BUFSIZ, 0, 0) != -1)
         printf("You wrote: %s", msgbuf.text);        /* ��ܦ��쪺�T�� */
      else 
         err_exit ("msgrcv failed\n");
      if (strncmp(msgbuf.text, "end", 3) == 0)
         break;
   }
   /* �����T����C */
   if (msgctl(msgid, IPC_RMID, 0) == -1) 
      err_exit("msgctl(IPC_RMID) failed\n");
   exit(EXIT_SUCCESS);
}
