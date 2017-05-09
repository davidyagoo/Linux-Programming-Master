#include "ch05.h"
#include "xmalloc.c"

int main(int argc,char *argv[])
{
   char *value;  
   if(argc==1||argc>3) {   /* �ˬd�I�s�ѼƬO�_���T*/
      fprintf(stderr, "Usage: <environ var> [<value>]\n");
      exit(1);
   }
  
   value = getenv(argv[1]); /* �������ܼƤ��� */
   if(value)
      printf("Variable %s = %s\n",argv[1],value);
   else
      printf("Variable %s undefined\n",argv[1]);
   if(argc==3){  /* �T�ӰѼƪ�����  */
      char *string = xmalloc(strlen(argv[1])+strlen(argv[2])+2);
      strcpy(string,argv[1]);  // �Φ�"name=value"  
      strcat(string,"=");
      strcat(string,argv[2]);
      printf("calling putenv with: %s\n",string);
      if(putenv(string)!=0){  /* �]�w�s�����ܼ�  */
         free(string);
         err_exit("putenv error");
      }
      value = getenv(argv[1]); /* �ֹ���ܼƪ��s��  */
      printf("New value of %s = %s\n",argv[1],value);
   }
   exit(0);
}
