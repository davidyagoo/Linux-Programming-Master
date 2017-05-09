#include "ch09.h"
struct termios saved_attributes;        /* �θ��ܼ��x�s��Ӫ��׺��ݩ� */
void resume_input_mode(void)
{
   tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);
}
void set_input_mode(int fd)
{
   struct termios tattr;
   char *name;
   if (!isatty(fd)) { /* �T�Ofd �O�׺� */
      fprintf(stderr, "Not a terminal.\n"); exit (EXIT_FAILURE);
   }
   tcgetattr(fd, &saved_attributes); /* �x�s�ثe�׺��ݩ�*/
	   /* �]�w�׺ݬ��D�[�u�B���^���Ҧ� */
   tcgetattr(fd, &tattr);
   tattr.c_lflag &= ~(ICANON|ECHO); /* �M�� ICANON�MECHO */
   tattr.c_cc[VMIN] = 1;  /* ���ݦܤ�Ū�@�Ӧr�� */
   tattr.c_cc[VTIME] = 0;
   tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}
int main (void)
{
   char c;
   set_input_mode(STDIN_FILENO);
   while (1){
       read (STDIN_FILENO, &c, 1);
       if (c == '\004')          /* Ctrl-d */
          break;
       else
          printf("I read %c\n",c);
    }
    resume_input_mode(); /* �٭�׺��ݩ� */
    return EXIT_SUCCESS;
 }
