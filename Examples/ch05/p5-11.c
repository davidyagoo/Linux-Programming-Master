#include <pwd.h>
#include <string.h>
struct passwd *getpwnam (const char *name)
{
   struct passwd *ptr;
   setpwent();                                  /* �}�ҨϥΪ̸�Ʈw */
   while((ptr = getpwent()) != NULL) {
      if (strcmp(name, ptr->pw_name) == 0)
         break;                                  /* ����ﶵ */
   }
   endpwent();                                  /* �����ϥΪ̸�Ʈw */
   return(ptr);                                 /* �䤣�����ptr��NULL */
}
