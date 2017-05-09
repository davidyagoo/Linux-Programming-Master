#include "ch05.h"
#define SCORES_FILE "/tmp/score"
static uid_t euid, ruid;  /* �x�s���ĩM���UIDS*/
void do_setuid(void)      /* �٭��Ӫ�����UID */
{
   int status;
#ifdef _POSIX_SAVED_IDS
   status = setuid(euid);
#else
   status = setreuid(ruid, euid);
#endif
   if (status < 0) 
      err_exit("Couldn't set uid");
}

void undo_setuid(void) /* �]�w����UID�����UID */
{   int status;
#ifdef _POSIX_SAVED_IDS
   status = setuid(ruid);
#else
   status = setreuid(euid, ruid);
#endif
   if (status < 0) 
      err_exit("Couldn't set uid");
}

int record_score(int score) /* �O���o�� */
{
   FILE *stream;
   char *myname;
   do_setuid ();     /* �������̦�Ū�g�o���ɮת��v�Q */
   stream = fopen (SCORES_FILE, "a");   /* �}�ұo���ɮ� */
   undo_setuid();    /* ���^������Ū�g�o���ɮת��v�Q,���v�T�᭱���g�J�ާ@ */
   /* �g�o���ܰO���ɮ� */
   if (stream) {
      myname = cuserid((char *)NULL);  /* ��������̪��ϥΪ̦W�� */
      if (score < 0)
         fprintf (stream, "%10s: Couldn't lift the caber.\n",myname);
      else
         fprintf (stream, "%10s: %d feet.\n", myname, score);
      fclose (stream);
      return 0;
   }
   else
      return -1;
}
int main(void)
{
   /* �x�s��کM���ĨϥΪ�IDs */
   ruid = getuid();
   euid = geteuid();
   undo_setuid();             /* �������̥u���L�ۤv���v�Q */
   /* �i������ðO���o�� */
   /* ... */
}
