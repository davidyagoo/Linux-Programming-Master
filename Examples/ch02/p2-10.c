#include "ch02.h"
int main(void)
{
   FILE *tempfp;
   char tmpname[L_tmpnam],*cp;
   char line[256];
   char *pfx = "XXXXX";
   if ((cp=tmpnam(tmpname))==NULL)  // �˵�tmpnam()���ͪ��ɦW
      printf("a unique name cannot be generate by tmpnam()\n");
   else
      printf("       file name get by tmpnam(): %s\n", cp);
   /* �˵�tempnam()���ͪ��ɦW */
   cp = tempnam("./", pfx);          
   printf("            by tempnam(\"./\",pfx): %s\n", cp);
   free(cp);
   cp = tempnam("/not_exist_dir/", pfx);
   printf("by tempnam(\"/not_exist_dir\",pfx): %s\n", cp);
   free(cp);
    /* ��tmpfile()�إߤ@�ӼȦs�� */
   if ((tempfp=tmpfile()) == NULL)
      err_exit("tmpfile error");
   printf("tmpfile() created a temporary file\n");
   /* ���Ȧs�ɼg�J�@����,�M��N��Ū�X�üg�ܼЭ��X�i������ */
   fputs("One line of output\n", tempfp);
   rewind(tempfp);
   if(fgets(line, sizeof(line), tempfp) == NULL)
      err_exit("fgets error");
   fputs(line,stdout); 
   exit(0);
}
