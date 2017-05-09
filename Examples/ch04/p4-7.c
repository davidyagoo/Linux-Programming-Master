#include "ch04.h"

int main(int argc, char*argv[])
{  
   long int length;
   int fd;
   char *cp;
   
   if (argc != 3){   /* 浪琩把计タ絋┦ */
      printf("usage: a.out <filename> <file size>\n");
      exit(1);
   }

   /* 弄把计秨币郎 */
   length = strtol(argv[2], &cp, 10); 
   if (cp==argv[2]) {  /* 材把计獶计 */
      printf("usage: a.out <filename> <file size> and "
             "<file size> must be a integer\n");
      exit(1);
   }

   if ((fd = open(argv[1],O_RDWR)) < 0)
      err_exit("open() call failed");

   /* 材把计﹚じ舱掉耞郎 */
   printf ("truncate %s to %d characaters\n", argv[1], length);
   if ( ftruncate(fd, length) < 0 ) 
      err_exit("truncate() call failed");
   printf ("truncate() call successful\n");

   lseek(fd,(long)0, SEEK_END); /* ﹚郎Ю */
   write(fd, "@T" ,2);          /* 糶Ю场夹粁 */

   close(fd);
}
