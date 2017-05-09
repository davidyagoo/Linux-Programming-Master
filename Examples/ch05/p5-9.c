#include "ch05.h"
static void setup_core_dumping (void)
{
   struct rlimit rlim;
   if (getrlimit(RLIMIT_CORE, &rlim) != 0)   /* ���o�����  */
      err_exit("getting core file size maximum limit ");
   rlim.rlim_cur = rlim.rlim_max;              /* �εw����m���n����  */
   if (setrlimit(RLIMIT_CORE, &rlim) != 0)   /* ���s�]�w�����  */
      err_exit("setting core file size limit to maximum ");
}
