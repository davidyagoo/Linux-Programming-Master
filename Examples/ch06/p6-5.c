#include "ch06.h"
#include "p6-3.c" //pr_exit()

/*  parse--����buf�������O���W�ߪ��Ѽ�  */
void parse(char *buf, char *args[])
{
   int i=0;
   while (*buf != '\0') {
      /* �ΪŦr��'\0'���N�ťզr���ϱo�e�@�ѼƥH�Ŧr������  */       
      args[i++]=buf;
      while ((*buf!=' ')&&(*buf!='\t')&&(*buf!='\n')) buf++;
      while ((*buf==' ')||(*buf=='\t'||(*buf=='\n'))) *buf++ = '\0';
   }
   args[i]='\0';
}

/*  execute--�l�ͤ@�l��������榹�{��  */
void execute(char *args[])
{
   int pid, status;
   /*  �إߤ@�l�����  */
   if ((pid=fork()) <0) 
      err_exit("fork");
   /*  �l���������if�����{���X  */
   if (pid==0) {
      execvp(*args,args);
      err_exit("execvp");
   } 
   /*  ����������ݤl���������  */
   waitpid(pid, &status, 0);
   pr_exit(status,pid);
}
int main(void)
{
   char buf[1024];
   char *args[64], *cp;

   for (;;) {
     printf("Command: ");   // �|�X���ܲ�
     cp = fgets (buf, sizeof(buf), stdin);    //Ū�J���O
     if (cp == (char *)NULL || *cp == '\n'){  // �Ŧ������}
        printf("quit\n");
        exit(EXIT_SUCCESS);
     }
     /*  ���Ѧr�ꬰ�Ѽ�  */
     parse(buf, args);
     /*  ������O  */
     execute(args);
   }
}

