#include "ch13.h"
#define NUM_THREADS    4 

void Hello(void * t)     /* 執行緒開始函數 */
{
   pthread_t my_tid;
   my_tid = pthread_self();   /* 獲得目前執行緒TID */
   printf("\tThread %d: my tid is %lx, Hello World!\n", t, my_tid);
}
int main ()
{
   pthread_t tid;
   int rv, t;
   for(t=0; t<NUM_THREADS; t++){
      rv = pthread_create(&tid, NULL, (void *(*)())Hello, (void*)t);
      check_error(rv, "pthread_create()" )
      printf("Created thread %lx\n", tid);
   }
   printf("Good bye\n");
   pthread_exit(NULL);     /* 終止執行緒 */
}
