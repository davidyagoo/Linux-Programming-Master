#include "ch11.h"
void write_data (FILE * stream)
{
    int i;
    for (i = 0; i<50; i++){        /* ��X50�Ӿ��*/
       fprintf (stream, "line %2d\n", i);
       if (ferror (stream)) 
           err_exit("Output to stream failed.\n");
    }
}
int main (void)
{
    FILE *output;
    /* �إ߰���more�������������ܿ�J,�ëإ߳q�V������J�޽u */
    output = popen ("more -10", "w");
    if (!output) 
        err_exit("Could not run more.\n"); 
    write_data (output);
    /* ����popen�إߪ�������פ�������P���۳s���y */
    pclose (output);
    return EXIT_SUCCESS;
}
