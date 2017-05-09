#include "ch09.h"
#define TTY_OUTPUT 1
static struct termios old_term, new_term;
void do_exit(int);
void set_tty()
{
   /* ���B�z����M����šA����BREAK���� */
   new_term.c_iflag &= ~(ICRNL|IGNCR|INLCR|IGNBRK|BRKINT);
   new_term.c_oflag &= ~OPOST;           /* �L��{�w�q����X�B�z */
   new_term.c_lflag |= ISIG | NOFLSH;    /* ���Ͳ׺ݰT���A�����M����X��C */
   new_term.c_lflag &= ~(ICANON);        /* �D�[�u�Ҧ� */
   new_term.c_cc[VINTR] = 7;              /* Ctrl-g �@�����_�r�� */
   new_term.c_cc[VQUIT] = 8;              /* Ctrl-h �@�����}�r�� */
   new_term.c_cc[VMIN]  = 1;
   new_term.c_cc[VTIME] = 0;
   tcsetattr(TTY_OUTPUT, TCSADRAIN, &new_term);
}
void tty_init()
{
   tcgetattr(TTY_OUTPUT, &old_term);
   new_term = old_term;         /* �x�s�׺ݰ_�l���A */
   signal(SIGTERM, do_exit);
   signal(SIGQUIT, do_exit);
   signal(SIGINT,  do_exit);
   set_tty();
}
void tty_end()
{
   tcsetattr(TTY_OUTPUT, TCSADRAIN, &old_term);
}
void do_exit(int signum)
{
   tty_end();
   exit(1);
}
int main()
{
   char c;
   printf("Display key sequence utility\n");
   printf("Press space when done.\n\n");
   tty_init();
   for (;;) {
      read(0, &c, 1);
      if (c == ' ')
          break;
      printf("%o\n", c);
      fflush(stdout);
   }
   tty_end();
   return 0;
}

/* �ﵽ���� */
/*
void restore_tty()
{
   signal(SIGTSTP, SIG_DFL);                     /* �w�]�T������X�A����{�� */
   tcsetattr(TTY_OUTPUT, TCSADRAIN, &old_term);  /* �٭�׺ݬ���Ҧ� */
   raise (SIGTSTP);                              /* �A�����͸ӰT����shell */
}
void tty_end()
{
   signal(SIGTSTP, restore_tty); 
   tcsetattr(TTY_OUTPUT, TCSADRAIN, &old_term);
}
void tty_init()
{
   tcgetattr(TTY_OUTPUT, &old_term);
   signal(SIGTERM, do_exit);
   signal(SIGQUIT, do_exit);
   signal(SIGINT,  do_exit);
   signal(SIGTSTP, restore_tty); 
   signal(SIGCONT, set_tty);
   new_term = old_term;
   set_tty();
}
*/
