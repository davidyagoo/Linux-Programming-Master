#include "ch02.h"
int y_or_n_ques(const char *question)
{
   fputs (question, stdout);     /* ��X���� */
   while(1){
      int c, answer;
      fputc (' ', stdout);       /* �g�@�Ů���}���D�P�^�� */
       /* Ū����Ĥ@�Ӧr��.������O�^���r���A���]�i�ण�O. */
      c = tolower(fgetc (stdin));
      answer = c;
      while(c != '\n' && c != EOF)   /* �������檺��E�r��. */
          c = fgetc(stdin);
       /* �Y�G�O�^���r���A�T���^��. */
      if (answer == 'y')
          return 1;
      if (answer == 'n')
          return 0;
       /* �D�^���r���A�~��n�D�X�k�^��. */
      fputs ("Please answer y or n:", stdout);
   }
}
