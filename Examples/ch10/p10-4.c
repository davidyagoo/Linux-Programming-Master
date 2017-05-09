#include "filelock.h"
static void lockabyte(const char *, int , off_t);
int main(void)
{
   int fd;
   pid_t pid;
   /* �إ��ɮרüg��Ӧ줸��*/
   if ((fd = creat("templock", 0666)) < 0)
       err_exit("creat error");
   write(fd, "ab", 2) ;
   if((pid = fork())==0) {              /* �l����� */
       lockabyte("child", fd, 1);
       sleep(2);                /* �d�X�ɶ��H�K����������줸��2 */
       lockabyte("child", fd, 2);
   } else {                      /* ������� */
       lockabyte("parent", fd, 2);
       sleep(2);                /* �d�X�ɶ��H�K�l��������줸��1 */
       lockabyte("parent", fd, 1);
   }
   exit(EXIT_SUCCESS);
}
static void lockabyte(const char *name, int fd, off_t offset)
{
   if (SET_LOCK_W(fd, F_WRLCK, offset, SEEK_SET, 1) < 0 ) {
      printf("%s: unable to set clock on byte %d, %s\n",name,
                  (int)offset, strerror(errno));
      exit(EXIT_FAILURE);
   }
   printf("%s: set lock on byte %d success\n",name, (int)offset);
}
