#include "ch05.h"
typedef enum{
  ST_PROGRAM, ST_FUNCTION, ST_SUBROUTINE, ST_END, ST_NONE // �䥦�ԭz���A...
} statement;
jmp_buf eof_buf;
int parse_file(void)
{
   statement st;
   if (setjmp(eof_buf)){  /* �]�w�X���Ǧ^�I */
      error("Unexpected end of file in '%s'", source_file);
      return FAILUR;	 /* �J��D�зǪ�EOF  */
   }
   while((st = next_statement())!= ST_NONE)  /* �зǪ�EOF�A�������y  */
      switch (st) {
      case ST_PROGRAM:     /* �q���ԭz  */
      case ST_SUBROUTINE:
      case ST_FUNCTION:
          accept_statement(st);
          parse_progunit(); 
          break;
          /* �䥦�q���ԭz�B�z  */
      }
   /* ���~�B�z ...  */  
   return SUCCESS;
}
void parse_progunit()
{ 
   statement st;
   st = parse_spec();        /* ���y�����ԭz  */
   if (st == ST_NONE)
	  longjmp(eof_buf, 1);  /* �J��D�зǪ�EOF�A�����Ǧ^��D���L�{  */
   else if (st == ST_END) {   /* �q���ԭz  */
      accept_statement(st);
      goto done;
   }
   parse_executable(st);     /* ���y����ԭz  */
done: ; /* ���~�B�z  */
}
parse_executable(statement st)  /* ���y����ԭz�A���t�q���ԭz  */
{
   for (;; st = next_statement())
      switch (st) {
	  case ST_NONE:  
	     longjmp (eof_buf, 1); /* �J��D�зǪ�EOF�A�����Ǧ^��D���L�{  */
	  case ST_END:      /* �q���ԭz  */
	     accept_statement(st);
	     return;
	  case ST_IF_BLOCK:
	     parse_if_block();
	     continue;
	  case ST_DO:
	     parse_do_block();
	     continue;
	  /* �䥦�i����ԭz�B�z...  */
	 }
}
