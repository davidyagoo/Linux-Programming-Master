#include "ch04.h"
void * xmalloc(int);     /* �{��5-6 */
read_specs(char *filename)
{
   int desc;
   struct stat statbuf;
   char *buffer;
   register char *p;
   desc = open(filename, O_RDONLY, 0);    /* �}���ɮרè��o�ɮװT�� */
   if (desc < 0)
     err_exit(filename);
   if (stat(filename,&statbuf) < 0)
     err_exit(filename);
   /* ��buffer���t�j�p��st_size���Ŷ� */
   buffer = xmalloc ((unsigned)statbuf.st_size + 1); 
   read (desc,buffer,(unsigned)statbuf.st_size);     /* Ū����ɮפ��e��buffer */
   buffer[statbuf.st_size] = 0;
   close (desc);
   /* �B�zŪ�J���ɮסA... */
}
