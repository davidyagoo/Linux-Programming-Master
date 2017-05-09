#include "ch03.h"
int main (int argc, char **argv)
{
   int n, from, to;
   char buf[1024] ;
   if (argc != 3) {      /* �ˬd�ѼƭӼơC*/
      printf("Usage : %s from-file to-file\n", argv[0]);
      exit (1);
   }
   if ((from = open (argv[1],O_RDONLY)) < 0)  /* ��Ū�Ӷ}���ɮ�from */
      err_exit (argv[1] ); 
  /* �H�[�J�Ҧ��}���ɮ�to. �Y�ɮפ��s�b�Aopen() �N�H�Ҧ�644�]-rw-r--r--)�إߥ��C*/
   if ((to = open(argv[2], O_WRONLY|O_CREAT|O_APPEND, 0644)) < 0)
      err_exit (argv[2] );
   /* �q�ɮ�fromŪ��ƨüg��to.�C���g�X���r���ӼƬO�C��Ū�J���r���Ӽ� */
   while ((n = read(from, buf, sizeof(buf))) > 0)
       write (to, buf, n) ;
   close(from) ;     /* �����ɮ� */
   close(to) ;
}
