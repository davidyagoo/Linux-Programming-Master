#include "ch02.h"
int main (int argc, char *argv[])
{
   int n;
   FILE *from, *to;
   char buf[BUFSIZ] ;
   if (argc != 3) {    /*�ˬd�ѼơC*/
      fprintf(stderr, "Usage : %s from-file to-file\n", *argv) ;
      exit (1);
   }
   if ((from = fopen(argv[1],"r")) == NULL)  /* ��Ū�Ӷ}���ɮ�from */
      err_exit (argv[1] ) ; 
	   /* �H�[�J�Ҧ��}���ɮ�to. �Y���ɮפ��s�b�Afopen �N�إߥ��C*/
   if ((to=fopen(argv[2], "a")) == NULL)
      err_exit(argv[2] ) ;
	   /* �{�b�C���i�H�q�ɮ�fromŪ�J�üg��to. �`�N�ڭ̼g�X���r���ӼƬO���Ū�J
      ���r���ӼƦӤ��`�OBUFSIZ�줸�աC*/
   while ((n = fread(buf, sizeof(char),BUFSIZ,from)) > 0)
      fwrite (buf, sizeof(char),n,to) ;
	   /*�����ɮ�*/
   fclose (from) ;
   fclose (to) ;
   exit (0) ;
}
