#include "ch09.h"
/*���O���*/
char *menu[]={"a-add new record", "d-delete record", "q-quit", NULL}; 
int getchoice(char *greet, char *choices[])
{
   int selected, chosen = 0;
   char **option;
   do{
      printf( "Choice: %s\n", greet);
      option = choices;
	  while(*option) {     /* �C�L��� */
          printf ("%s\n", *option);
          option++;
      }
      selected = getchar();  /* Ū�J���O�r�� */
      option = choices;
      while(*option){         /* �ˬd���O�r���A���T�h�mchosen=1*/
         if(selected == *option[0]) {
            chosen = 1;
            break;
         }
         option++;
	  }
      if(!chosen)   /* �Y���O�����T�A���ܭ��s��J���O�A����o�쥿�T�����O*/
      printf("Incorrect choice,please select agian\n");
   } while(!chosen); 
   return selected;
}
int main(void)
{
   int choice = 0;
   do {
      choice = getchoice("Please select a action", menu);
      printf ("Your choice is: %c\n", choice);
   } while (choice != 'q') ;
   exit (0);
}
