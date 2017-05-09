#include "ch04.h"
int main(int argc, char *argv[])
{
   char *ptr = malloc(PATH_MAX + 1);
   if (argc != 2){
      printf ("Usage: a.out <pathname>\n");
      exit (EXIT_FAILURE);
   }
   if (getwd(ptr)==NULL)        // �˵��ثe�u�@�ؿ�
      err_exit("getwd failed");
   printf("Current work directory is :%s\n", ptr);
   if (chdir (argv[1]) < 0)    //���ܤu�@�ؿ�
      err_exit("chdir failed");
   if (getwd(ptr)==NULL)       //�˵��s���u�@�ؿ�
      err_exit("getwd failed");
   printf("CWD = %s\n",ptr);
   free(ptr);
}
