#include "ch03.h"
int main(void)
{
   int fd;
   if((fd = open("myoutput",O_WRONLY|O_CREAT,0644)) == -1)
      err_exit("myoutput");
   if(dup2(fd,STDOUT_FILENO) == -1)    /* ���_�Э��X��fd�۳s���ɮ�myoutput */
      err_exit("Redirect standard output failed");
   printf("this is a test program for redirect \n");
   close(fd);
}
