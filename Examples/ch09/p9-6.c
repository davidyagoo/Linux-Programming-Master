#include "ch09.h"
int main(void)
{
   int  n1, n2, fd;
   if((fd=open("/dev/ttyS0", O_RDWR|O_NOCTTY|O_NONBLOCK))== -1){
      fprintf(stderr, "Open port: Unable to open, %s\n",strerror(errno));
      exit(EXIT_FAILURE);
   }
   write(fd, "Example of line control functions ", 34);
   tcdrain(fd);             /* ���ݿ�X��C������ƥ����e�X */
   tcflow(fd, TCOOFF);      /* �a����X�ǿ� */
   n1 = write(fd, "this line will be thrown over\n", 30);
   tcflush(fd, TCOFLUSH);   /* �M����X��C */ 
   n2 = write(fd, "this line will not be thrown over\n", 34);
   tcflow(fd, TCOON);       /* �٭��X�ǿ� */
   write(fd,"restart the output\n",19);
   exit(EXIT_SUCCESS);
}
