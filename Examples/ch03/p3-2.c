#include "ch03.h"
char bufl[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
int main (void)
{
    int fd;
    if ((fd = open("file.hole",O_WRONLY|O_CREAT/*|O_APPEND*/, 0644)) < 0)
        err_exit("creat error" );
    if (write (fd, bufl, 10) != 10)
        err_exit("buf1 write error");
	    /* �ɮץثe��m��10�A�{�b�N������40 */
    if (lseek(fd, 40, SEEK_SET) == -1)
        err_exit("lseek error");
	    /* �ɮצ�m�{�b��40 */
    if (write (fd, buf2, 10) != 10)
       err_exit("buf2 write error");
	    /* �ɮצ�m�{�b��50 */
    exit(0);
}
