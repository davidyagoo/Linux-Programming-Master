#include <stdio.h>
//#include <ctype.h>
void skip_whitespace (FILE *stream)
{
    int c;
    do
      c = getc (stream);  /* �L���ˬdEOF�A�]�������O�ťզr���Bungetc����EOF. */
    while (isspace (c));
    ungetc (c, stream);
}
