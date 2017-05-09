#include "ch04.h"

int main(int argc, char*argv[])
{  
   long int length;
   int fd;
   char *cp;
   
   if (argc != 3){   /* �ˬd�Ѽƪ����T�� */
      printf("usage: a.out <filename> <file size>\n");
      exit(1);
   }

   /* Ū���Ѽƨö}���ɮ� */
   length = strtol(argv[2], &cp, 10); 
   if (cp==argv[2]) {  /* �ĤG�ѼƫD�Ʀr */
      printf("usage: a.out <filename> <file size> and "
             "<file size> must be a integer\n");
      exit(1);
   }

   if ((fd = open(argv[1],O_RDWR)) < 0)
      err_exit("open() call failed");

   /* ���ĤG�Ѽƫ��w�줸�յ��_�ɮ� */
   printf ("truncate %s to %d characaters\n", argv[1], length);
   if ( ftruncate(fd, length) < 0 ) 
      err_exit("truncate() call failed");
   printf ("truncate() call successful\n");

   lseek(fd,(long)0, SEEK_END); /* �w����ɮק� */
   write(fd, "@T" ,2);          /* �g�J�����лx */

   close(fd);
}
