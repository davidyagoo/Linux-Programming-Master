/* �Yvalue�D0�A�]�wFD_CLOEXEC�Ч�,�Yvalue��0,�M���ӼЧӡC���\�Ǧ^0�A���ѶǦ^-1*/
#include "ch03.h"
int set_cloexec_flag (int desc, int value)
{
   int oldflags = fcntl (desc, F_GETFD, 0);
   if(oldflags < 0)    /* �YŪ��ñ���ѡA���~�Ǧ^�C*/
       return oldflags;
   /* �]�w�ݭn���Ч�. */
   if(value != 0)
       oldflags |= FD_CLOEXEC;
   else
      oldflags &= ~FD_CLOEXEC;
   return fcntl (desc, F_SETFD, oldflags); 
}
