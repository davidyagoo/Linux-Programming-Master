#include "ch04.h"
#include "get_perms.c"  /* �{��4-4 */
#define BLKSIZE 1024
void list(char *);
void printout(char *, char *);

int main(int argc, char *argv[])
{ 
   struct stat sbuf;
  
   if (argc < 2){  /* �Y�L�Ѽ�,�C�X�ثe�ؿ� */
      list(".");
      exit(0);
   }

   /* �B�z�Ѽ� */
   while(--argc){
     if (stat(*++argv,&sbuf) < 0) {  /* �˵��ɮ׫��A */
        perror(*argv);
        continue;
     }
     /* �Y�G�O�ؿ��A�N���C�X�A�_�h�C�L�X�ɮת����A�T�� */
     if ((sbuf.st_mode &S_IFMT) == S_IFDIR)
        list(*argv);
     else
        printout(".",*argv);
   }
   exit(0);
}

/* Ū�@�ӥؿ��æC�X�䤤���ɮ� */
void list(char *name)
{
   DIR *dp;
   struct dirent *dir;
   if ((dp = opendir(name)) == NULL) { /*  �}�Ҹӥؿ�  */
      fprintf(stderr, "%s: cannot open.\n",name);
      return;
   }

   while((dir = readdir(dp)) != NULL)  /*  �B�z�C�@�ӥؿ� */
      printout(name, dir->d_name);
   closedir(dp);
}

void printout(char *dir, char *name)  /* �C�L�X�ɮת������T�� */
{
   int i,j;
   char perms[10];
   struct stat sbuf;
   char newname[BLKSIZE];

   sprintf(newname,"%s/%s",dir,name);   /* �Φ����|�W */
   stat(newname,&sbuf);/* ���ɥi�H�֩w���ɮצs�b�A�G������������ */
   /* �C�L�ɮת��϶��j�p�A�C����BLKSIZE�줸�� */
   printf("%5d",(sbuf.st_size+BLKSIZE-1)/BLKSIZE);
   /* ����æC�L�ɮ׫��A */
   switch(sbuf.st_mode & S_IFMT){
     case S_IFREG:  putchar('-'); break;
     case S_IFDIR:  putchar('d'); break;
     case S_IFCHR:  putchar('c'); break;
     case S_IFBLK:  putchar('b'); break;
     case S_IFIFO:  putchar('l'); break;
#ifdef S_IFLNK
     case S_IFLNK:  putchar('l'); break;
#endif
#ifdef S_IFSOCK
     case S_IFSOCK: putchar('l'); break;
#endif
     default:       putchar('?'); break;
   }
  
   get_perms(&sbuf, perms);  /* ���o�T�s�զs���v���]���{��4-4�^ */
   /* �C�L�s���v���B�s���ơB�ϥΪ�ID�M�s��ID */
   printf("%s%3d %5d/%-5d ", perms, sbuf.st_nlink, sbuf.st_uid,
                   sbuf.st_gid);
   /* �C�L�ɮפj�p�M�ק�ɶ��Cctime�ഫ�@�Ӯɶ���ASCII�r�� */
   printf("%7d %.20s ",sbuf.st_size, ctime(&sbuf.st_mtime));
   printf("%s\n", name); /* �̫�A�C�L�ɦW */
}
