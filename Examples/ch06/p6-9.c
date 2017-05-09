#include "ch06.h" 

 /* �@�� process �N��@�Ӱ����.  */
typedef struct process
{
   struct process *next;       /* next process in pipeline */
   char **argv;                /* for exec */
   pid_t pid;                  /* process ID */
   char completed;             /* true if process has completed */
   char stopped;               /* true if process has stopped */
   int status;                 /* reported status value */
} process;

/* �@��job �N��Ѻ޽u�s�u���\�h�Ӱ�����s�զ����@�ӧ@�~.  */
typedef struct job
{
   struct job *next;           /* next active job */
   char *command;              /* command line, used for messages */
   process *first_process;     /* list of processes in this job */
   pid_t pgid;                 /* process group ID */
   char notified;              /* true if user told about stopped job */
   struct termios tmodes;      /* saved terminal modes */
   int jstdin, jstdout, jstderr;  /* standard i/o channels */
} job;

/* ���D���@�~�s�զ��쵲��C�C�o�O����Y */
job *first_job = NULL;

pid_t shell_pgid;     
struct termios shell_tmodes;
int shell_terminal;
int shell_is_interactive;

/* �T�O��shell �b�}�l�u�@���e�O���ʰ��檺�e���@�~ */
void init_shell(void)
{
   /* �ˬd�O�_���ʰ���A�Y�P�w�PSTDIN_FILENO�۳s���O�_�׺� */
   shell_terminal = STDIN_FILENO;
   shell_is_interactive = isatty(shell_terminal);
   shell_pgid = getpid();

   if (shell_is_interactive) {  /* �O���ʰ���shell */
      /* �ˬd�O�_�b�e������A�Y�G������s��ID���P�󱱨�׺ݪ�������s��ID�h�O�b�I������A
         �]�ӥ�Ž�v�e����T���A���L�{�`������ϥΪ̱N�ۤv��m��e�� */
      while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
         kill(- shell_pgid, SIGTTIN);
      /* �������ʩM�@�~����T�� */
      signal(SIGINT, SIG_IGN);
      signal(SIGQUIT, SIG_IGN);
      signal(SIGTSTP, SIG_IGN);
      signal(SIGTTIN, SIG_IGN);
      signal(SIGTTOU, SIG_IGN);
      signal(SIGCHLD, SIG_IGN);
      /* �]�wshell��������s�� */
      if (setpgid(shell_pgid, shell_pgid) < 0)
         err_exit("Couldn't put the shell in its own process group");
      /* �m�ܱ���׺� */
      tcsetpgrp(shell_terminal, shell_pgid);
      /* �x�sshell���w�]�׺��ݩʥH�K���}���٭� */
      tcgetattr(shell_terminal, &shell_tmodes);
   }
}

void launch_process (process *p, pid_t pgid, int infile, 
                     int outfile, int errfile, int foreground)
{
   pid_t pid;

   if (shell_is_interactive) {
      /* ��m�Ӱ�����ܰ�����s�աC�]���v�����t�G�A�l������Mshell�G�̳������o�˰� */
      pid = getpid();
      if (pgid == 0)          /*  pgid ��0��ܳo�O������s�ժ��Ĥ@�Ӱ���� */       
         pgid = pid;         /*  �ϥ�����������s�ոs�ժ� */
      setpgid(pid, pgid);
      /*�Y�O�e��������A��������s�ձ���׺ݡC*/ 

      if (foreground)
         tcsetpgrp(shell_terminal, pgid);

      /* �]�w�@�~����T��������X�^��w�] */
      signal(SIGINT, SIG_DFL);
      signal(SIGQUIT, SIG_DFL);
      signal(SIGTSTP, SIG_DFL);
      signal(SIGTTIN, SIG_DFL);
      signal(SIGTTOU, SIG_DFL);
      signal(SIGCHLD, SIG_DFL);
   }

   /* �]�w�s��������Э�I/O�q�D */
   if (infile != STDIN_FILENO) {       /* �޽u��J����  */
      dup2(infile, STDIN_FILENO);    /* �ƻs�޽u�y�z�r�ܼЭ��J�y�z�r */
      close(infile);                 /* �����޽u�y�z�r�A�H�U���O�� */
   }
   if (outfile != STDOUT_FILENO) {
      dup2(outfile, STDOUT_FILENO);
      close(outfile);
   }
   if (errfile != STDERR_FILENO) {
      dup2(errfile, STDERR_FILENO);
      close(errfile);
   }

   /* ����s����� */
   execvp (p->argv[0], p->argv);
   err_exit("execvp");
}

void launch_job(job *j, int foreground)
{
   process *p;
   pid_t pid;
   int mypipe[2], infile, outfile;

   infile = j->jstdin;      /* �Ĥ@�Ӱ�������Э��J�ѫ��O���y�{�����w */
   for (p = j->first_process; p; p = p->next) {
      /* ���U�@�Ӱ�����A�h�O�κ޽u�s�u���C�إߺ޽u
         �ϱo�o�Ӱ��������X�����U�@�Ӱ��������J */
     if (p->next) {       
        if (pipe(mypipe) < 0) 
           err_exit("pipe");
        outfile = mypipe[1];
     } else
        outfile = j->jstdout;
     /* Fork �l����� */
     if ((pid = fork()) < 0)    
        err_exit("fork");
     if (pid == 0)          /* �l����� */
        launch_process(p, j->pgid, infile, outfile, j->jstderr, foreground);
     else{                    /* ������� */
        /* ��m�Ӱ�����ܰ�����s�աC�]���v�����t�G�A�l������Mshell�G�̳������o�˰� */
        p->pid = pid;
        if (shell_is_interactive) {
           if (!j->pgid)
              j->pgid = pid;      /* �O���@�~��������s��ID */
           setpgid(pid, j->pgid);
        }
     }
     /* �إߺ޽u���᪺�M�z�u�@ */
     if (infile != j->jstdin)
        close(infile);
     if (outfile != j->jstdout)
        close(outfile);
     infile = mypipe[0];    /* �U�@�Ӱ�������Э��J�O�o�Ӱ�������޽u��X */     
   }
   format_job_info(j, "launched");  /* �榡�ƿ�X�@�~���A�T�� */
   if (!shell_is_interactive)
      wait_for_job(j);
   else if (foreground)
      put_job_in_foreground(j, 0);
   else
      put_job_in_background(j, 0);
}

void put_job_in_foreground(job *j, int cont)
{
   /*  ��m�ӧ@�~��e��.  */
   tcsetpgrp(shell_terminal, j->pgid);
   /*  �Y�G�����n�A�V�ӧ@�~�ǰe�@�~��T��.  */
   if (cont) {
      tcsetattr(shell_terminal, TCSADRAIN, &j->tmodes);
      if (kill(- j->pgid, SIGCONT) < 0)
         perror("kill (SIGCONT)");
   }
   wait_for_job(j);/*  ���ݥ������i.  */
   tcsetpgrp (shell_terminal, shell_pgid);   /*  ��shell���s�^��e��.  */
   /*  �٭�shell���׺ݼҦ�.  */
   tcgetattr(shell_terminal, &j->tmodes);
   tcsetattr(shell_terminal, TCSADRAIN, &shell_tmodes);
}

/* ��m�@�ӧ@�~�ܭI���C�Y�Gcont �ѼƬ��u�A�h�V������s�նǰe�@��SIGCONT�T���H����� */
void put_job_in_background(job *j, int cont)
{
   /* �Y�����n�A�V�ӧ@�~�ǰe�~��T���C*/
   if (cont)
      if (kill(-j->pgid, SIGCONT) < 0)
         perror("kill (SIGCONT)");
}
