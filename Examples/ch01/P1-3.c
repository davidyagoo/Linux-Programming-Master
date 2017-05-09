#include "ch01.h"

char *get_current_dir()
{
    char *buffer;
    char *value;
    int size = 0;
    /*�T�w�ثe�u�@�ؿ����|�W���̤j���ש�size,��PATH_MAX ���T�w�ɡAsize��-1*/
#ifdef PATH_MAX
    size = PATH_MAX;
#else
    errno = 0;
    if ((size = pathconf("./",_PC_PATH_MAX)) < 0)
    if (errno != 0){
        printf("pathconf error for _PC_PATH_MAX\n");
        exit(-1);
    }
#endif
    if (size > 0){ /* PATH_MAX���w�q,�i�H�T�O���t���Ŷ����H�s����|�W*/
        buffer = (char *)malloc(size+1);
        value = getcwd(buffer, size);
    }else{  /* PATH_MAX�S���w�q,�����ձ��ʦa���t�������Ŷ��Ӧs����|�W*/
        size = _POSIX_PATH_MAX;
        buffer = (char *)malloc(size);
        while (1) {
            value = getcwd(buffer, size);
            if (value == 0 && errno ==ERANGE){ /* buffer�Ӥp�A���s�ӽЧ�j���Ŷ� */
               size *= 2;
               free (buffer);
               buffer = (char *) malloc (size);
            }
        } 
    }
    return buffer;
}
