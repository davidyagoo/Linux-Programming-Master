#include "ch09.h"
int set_termios(int desc)
{
    struct termios settings;
    int result;    
    result = tcgetattr(desc, &settings); /* ���o�ثe�׺��ݩ� */
    if (result < 0) {
        perror("error in tcgetattr"); return 0;
    }
    settings.c_iflag &= ~ISTRIP;    /* �M��ISTRIP */
    settings.c_lflag &= ~(ICANON | ECHO | ISIG);  /* �]�w�D�[�u��J */
    settings.c_oflag |= OPOST ;                   /* �]�w��{�w�q����X�B�z */
    result = tcsetattr(desc, TCSANOW, &settings); /* �Ϸs�]�w�ߧY�ͮ� */
    if (result < 0) {
        perror("error in tcgetattr"); return 0;
    }
    return 1;
}
