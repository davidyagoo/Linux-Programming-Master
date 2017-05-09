#include "ch06.h"
#include "p6-3.c"  //pr_exit()

int zero=0;

int main(void)
{
   pid_t pid;
   int status;

   if ((pid = fork()) == 0)  /* �l�ͤl�����1 */
      exit(0);               /* �l�����1�з����} */
   if ((pid = fork()) == 0)  /* �l�ͤl�����2 */
      abort();      /* �l�����2����SIGABRT�T�����} */
   if ((pid = fork()) == 0) {   /* �l�ͤl�����3 */
      status/=zero;   /* �l�����3�]0�@���Ʋ���SIGFPE�T�����} */
      exit(0);
   }
   while ((pid = wait(&status)) >= 0) /* ���ݤl�����  */
      pr_exit(status, pid);
   perror("wait over");
   exit(EXIT_SUCCESS);
}
