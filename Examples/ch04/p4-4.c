#include "ch04.h"

char *get_perms(struct stat *sbuf, char *perms)
{
   static char *modes[] = {   /* �P�C�@�ئs���v���\�i�ȹ������r�� */
       "---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"
   };  
   int i,j;

   *perms = '\0';
   /* ���O��o�T�s�զs���v���ȡA�θӭȧ@���}�Cmodes�����ޡA�H�K��o�������r����Jperms */
   for (i=2; i>=0; i--) {
      j=(sbuf->st_mode>>(i*3)) & 07;
      strcat( perms,modes[j]);
   }
   /*  �B�z�վ�ID��Msticky�� */
   if ((sbuf->st_mode & S_ISUID) !=0)
      perms[2] = 's';
   if ((sbuf->st_mode & S_ISGID) !=0)
      perms[5] = 's';
   if ((sbuf->st_mode & S_ISUID) !=0)
      perms[8] = 't';
   return perms;
}
