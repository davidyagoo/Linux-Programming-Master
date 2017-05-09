#include "ch02.h"
#include "y_or_n_ques.c"
char buf[132];
int main(int argc, char *argv[])
{
   FILE *fd;
   fpos_t pos;
   if (!y_or_n_ques("Should we use append mode?")) {
     if ((fd = fopen("test_file","w+")) == NULL)  /* �H�g�Ҧ��}���ɮ�  */
        err_exit("fopen faild");
   } else {
     if ((fd = fopen("test_file","a+")) == NULL)  /* �H�[�J�Ҧ��}���ɮ�  */
        err_exit("fopen faild");
   }
   fputs("0123456789ABCDEFGHIJ ",fd);    /* �g�J�@���� */
	   /* �˵��ثe�ɮק���m */
   fseek(fd,0,SEEK_END);
   fgetpos(fd,&pos);
   printf("current file position is %ld\n",pos);
   fseek(fd,30,SEEK_END);   /* �w����ɮק�����30�줸�աA���˵��ثe�ɮק���m  */
   fgetpos(fd,&pos);	
   printf("Now we call fseek(fd,30,SEEK_END); "
            "current file position is %ld\n",pos);
   fputs("abcdefg",fd); 	 /* �g�J��� */
   printf("Now we write 7 bytes \"%s\"\n","abcdefg");
   fgetpos(fd,&pos);        /* �˵��ثe�ɮק���m */
   printf("current file position is %ld\n",pos);
   fclose(fd);
}
