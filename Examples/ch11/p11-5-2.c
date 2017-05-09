#include "p11-6-7.h"
int main()
{
   int server_fifo_fd, client_fifo_fd;
   struct data_to_pass my_request;
   char client_fifo_name[256];
   pid_t mypid;
   /* �}�ҪA�Ⱥ޽u */   
   server_fifo_fd = open(SERVER_FIFO_NAME, O_WRONLY);
   if (server_fifo_fd == -1) 
       err_exit("Sorry, no server");
   /* �إߥH�����ID�R�W���Ȥᱵ�����W�޽u */
   mypid = getpid();
   sprintf(client_fifo_name, CLIENT_FIFO_NAME, mypid);
   if (mkfifo(client_fifo_name, 0777) == -1)
       err_exit(client_fifo_name);
   /* �V�A�Ȱ�����s��ǰe�M������� */
   while (1) {
       /* �Φ����A�Ȱ��������� */
       printf ("Enter your request:");
       fgets (my_request.data, BUFFER_SIZE, stdin);
       if (strcmp(my_request.data,"bye\n")==0
                      ||strcmp(my_request.data, "BYE\n")==0)
           break;
       my_request.client_pid = mypid;
       /* �V�A�Ȱ�����o�X�ШD */
       write(server_fifo_fd, &my_request, sizeof(my_request));
       /* �q�A�Ȱ���������^���A�����A���}�ҫȤᱵ�����W�޽u */
       client_fifo_fd = open (client_fifo_name, O_RDONLY);
       if (client_fifo_fd != -1) {
           if (read (client_fifo_fd, &my_request, sizeof(my_request)) > 0) {
               printf ("---I get answer: %s\n", my_request.data);
           }
           close(client_fifo_fd); 
       }
    }
     /* �����A��FIFO�ò����Ȥᱵ��FIFO */   
    close(server_fifo_fd);
    unlink(CLIENT_FIFO_NAME);
    exit(EXIT_SUCCESS);
}
