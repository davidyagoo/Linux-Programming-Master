#include "ch04.h"

int main(int argc, char *argv[])
{
   /* �ˬd�ѼƦX�k�_ */    
   if (argc != 2){
      printf("usage: a.out <filename>\n");
      exit(1);
   }     
   /* �ˬd��ڨϥΪ̬O�_��Ū�v�� */
   if (access(argv[1],R_OK) < 0){              
      printf("access error for %s. ",argv[1]);
      if (errno == EACCES)
         printf("you are not the owner of this file!\n");
   }
   else
      printf("read access OK\n");
   /* �L�׬O�_����ڨϥΪ�Ū�v���A�����ն}�Ҹ��ɮ� */
   if (open(argv[1], O_RDONLY) < 0)
      printf("open error for %s\n",argv[1]);
   else
      printf("open for reading OK\n");
   exit(0);  
}
