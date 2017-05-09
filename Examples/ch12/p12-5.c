#include "ch12.h"

int make_un_socket(int type, const char *filename)
{
    struct sockaddr_un name;
    int sock;
    socklen_t size;

    /* �إ߮M���r */
    sock = socket(AF_UNIX, type, 0);
    if (sock < 0) 
        err_exit("socket");
    /* �R�W�M���r */
    name.sun_family = AF_UNIX;
    strcpy(name.sun_path, filename);
    /* ��}���j�p�O�ɦW�}�l�������P����פ��M�[1�]�Ω�פ�Ŧ줸�ա^*/
    size = sizeof(struct sockaddr_un) + 1;
    if (bind (sock, (struct sockaddr *)&name, size) < 0)
        err_exit("bind");
    return sock;
}
