#include <stdio.h>

int y_or_n_ques(const char *question)
{
    fputs (question, stdout);
    while (1){
        int c, answer;
         /* �g�@�Ů���}���D�P�^�� */
        fputc (' ', stdout);
         /* Ū���椤���Ĥ@�Ӧr��.������O�^���r���A���]�i�ण�O. */
        c = tolower (fgetc (stdin));
        answer = c;
         /* �������檺��E�r��. */
        while (c != '\n' && c != EOF)
            c = fgetc (stdin);
         /* �Y�G�O�^���r���A�T���^��. */
        if (answer == 'y')
            return 1;
        if (answer == 'n')
            return 0;
        /* �D�^���r���A�ШD�X�k�^��. */
        fputs ("Please answer y or n:", stdout);
    }
}
