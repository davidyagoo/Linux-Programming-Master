#include "ch06.h"
int main (void)
{
   pid_t pid;
   if ((pid = fork()) < 0)
      err_exit("fork error");
   else if (pid == 0) {	            /* �Ĥ@�Ӥl����� */
      if ((pid = fork()) < 0) 	    /* �A���l�ͤ@�Ӥl����� */
         err_exit("fork error ");
      else if (pid > 0) {
         printf("child exit\n");
         exit(EXIT_SUCCESS);	      /*  �פ�Ĥ@���l�ͪ��l����� */
      }
      /*  �o�O�ĤG�Ӥl�����.������������exit��,���Qinit�~��. */
      sleep(2);                 /* �b�����ݤl����������u�@  */
      printf("grandchild's parent pid = %d\n", getppid ());
      exit(EXIT_SUCCESS);
   }
   if (waitpid(pid, NULL, 0) != pid) 	    /*  ���ݲĤ@�Ӥl�����  */
      err_exit("waitpid error");
   printf ("parent exit\n");
   exit(EXIT_SUCCESS);
}
