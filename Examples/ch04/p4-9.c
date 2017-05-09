#include "ch04.h"

char outbuf[100];

int main(void)
{
   int   fdtmp, fdout, length;

   /* �إߤG���ɮסA�@�ӧ@�������ɮסA�@�ӧ@�����G�ɮ� */
   fdtmp = open("tmpfile", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
   fdout = open("outfile", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
   if ( fdtmp < 0 || fdout < 0) 
      err_exit("ERROR: creat file failed");

   /* �ߧY���������ɮ� */
  if ( unlink ("tmpfile") < 0 )
      err_exit("unlink call failed");

   /* �������ɮ׼g��ơA�ɺ޳o���ɮפw�g�����A�ڭ̲{�b���M�i�HŪ�g�� */
   length = write(fdtmp, "An example progamm for unlink().", 32);

   /* ��¶�����ɮ� */
   if(lseek(fdtmp, (long)0, SEEK_SET) < 0)
      err_exit("lseek call failed");

   /* �ƻs�����ɮצܵ��G�ɮ� */
   read(fdtmp, outbuf, length);
   write(fdout, outbuf, length);

   close (fdout);
}
