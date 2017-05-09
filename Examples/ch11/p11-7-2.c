#include "p11-7.h"

int main()
{
   int msgid, running = 1;
   struct my_msg msgbuf;
   struct msqid_ds buf;
   /* ��o�T����Cid */
   msgid = msgget((key_t)1234, 0666|IPC_CREAT);
   if (msgid == -1) 
       err_exit("msgget failed\n");
 
   /* �ϴ_�N�ϥΪ̿�J����ƶǰe�ܰT����C�A�r�ꡧend���Чӿ�J���� */
   while(running) {
       /* Ū��J�r��ܰT���w�R�� */
       printf("Enter some text: ");         
       fgets(msgbuf.text, BUFSIZE, stdin);
       msgbuf.my_msg_type = (long int)msgbuf.text[0]; /* �Ĥ@�Ӧr���@���T�����A */
       /* �V�T����C�ǰe�T���A����Ҧ� */
       if (msgsnd(msgid, (void *)&msgbuf, sizeof(struct my_msg), IPC_NOWAIT) == -1) 
          err_exit("msgsnd failed\n");
       /* �Y�G�O��end���A�����`�� */
       if (strncmp(msgbuf.text, "end", 3) == 0) 
          running = 0;
   }
   exit(EXIT_SUCCESS);
}
