#include "ch02.h"
#define BUF_SIZE 8

int main(void)
{
   FILE *fd;
   int fgets_yes;
   struct iobuf {
       char buf[BUF_SIZE];
       char others[BUF_SIZE];
   }buffer;
  
   memset(&buffer,'\0',sizeof(struct iobuf)); 
   do {
       /* �ШϥΪ̿���ϥ�fgets()�٬Ogets() */
       fgets_yes = y_or_n_ques("Should we read by fgets()?");
       fprintf(stdout,"please enter a line\n");
       if(fgets_yes) {   /* ��fgetsŪ��J��� */
          fgets(buffer.buf, BUF_SIZE, stdin);
          fprintf(stdout,"fgets() get string \"%s\"\n",buffer.buf);
          while(buffer.buf[strlen(buffer.buf)-1] != '\n'){ /* �@�楼Ū���A�~��Ū */
             fgets(buffer.buf, BUF_SIZE , stdin); 
             fprintf(stdout,"fgets() get string \"%s\"\n",buffer.buf);
          }
       } else {   /* ��getsŪ��J��� */
          gets(buffer.buf);
          fprintf(stdout,"gets() get string \"%s\"\n",buffer.buf);
       }
       /* �˵����챡�p */
       fprintf(stdout,"buffer.others is \"%s\"\n",buffer.others);
   } while (y_or_n_ques("continue?"));
   exit(0);
}

