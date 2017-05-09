#include "ch10.h"

void input_ready(int signo);
FILE *file;

int main(void)
{
   int flags;
   char buffer[64];
   struct termios newsettings,oldsettings;

   file=fopen("tstfile", "w");   // �}�ҿ�X�ɮ�
   signal(SIGIO, input_ready);   // �w��SIGIO�T������X
 // �]�w�Э��J���C��Ū�J�@�r�����D�[�u�Ҧ�
   tcgetattr(STDIN_FILENO, &oldsettings);
   newsettings = oldsettings;
   newsettings.c_lflag &= (~ICANON);
   newsettings.c_cc[VTIME] = 0;
   newsettings.c_cc[VMIN] = 1;
   tcsetattr(STDIN_FILENO, TCSANOW, &newsettings);
 // �]�w�Э��J���L����SIGIO�T���X��IO�Ҧ�
   fcntl(STDIN_FILENO, F_SETOWN, getpid());
   flags = fcntl(STDIN_FILENO, F_GETFL, 0);
   flags = flags | O_ASYNC;//|O_NONBLOCK;
   fcntl(STDIN_FILENO, F_SETFL, flags);
   while (1) sleep(1);  // �S����J�ɥ�
}

void input_ready(int signo) // ������J�A�ֿn�ܤ@����X�C�歺�r����q�פ�����
{
   char c,input[80];
   int n;
   static int i=0;

   if (read(STDIN_FILENO, &c, 1)>0) {
      if (c != '\n')
         input[i++]=c;
      else {
        input[i++]='\0';
        fprintf(file, "received %d SIGIOs, and Input line is: %s\n", i, input);
        i=0;
        if (input[0]=='q') {
           fclose(file);
           _exit(0);
        }
      }
   }
}
