#include "ch06.h"

void pr_exit(int status, pid_t pid)
{
   int sig;

   if (WIFEXITED(status))           /* �зǲפ�l�����  */
      printf("process %d normal termination, exit status = %d\n", pid,
              WEXITSTATUS(status));
   else if (WIFSIGNALED(status)){   /* �ҥ~�פ�l�����  */
      sig = WTERMSIG(status);
      printf("process %d abnormal termination, signal number = %d%s:\n", pid, sig,
#ifdef WCOREDUMP
              WCOREDUMP(status) ? "(core file generated)" : "");
#else
              "");
#endif
      psignal(sig, "");
   } else if(WIFSTOPPED (status)){   /* �Q����l�����  */
      sig = WSTOPSIG (status);
      printf("process %d stopped, signal number = %d: ", pid, sig);
      psignal(sig, "");
   }
}
