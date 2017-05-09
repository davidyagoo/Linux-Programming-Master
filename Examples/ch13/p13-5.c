#include "ch13.h"
#include <sys/mman.h>
#define STACK_GROWS_DOWN
#undef  STACK_GROWS_UP
void Hello(void)
{
   int array[512];
   printf("Hello, &array=%d\n", &array);
   Hello(); 
}
/* �ӽа�������|�Ŷ��ëإ߰��|����O�@�ϡC���|��}����b����ɤW�A���|�j�p�X�R���������� */
void *thread_stack_alloc(size_t size)   
{
   int pagesize;
   void *mem, *guard_addr, *stack_addr;
   if (size < PTHREAD_STACK_MIN){
     fprintf(stderr, " thread_stack_alloc: SIZE less than PTHREAD_STACK_MIN\n");
     exit(1);
   }
   /* �p����|�j�p�������㭿�� */
   pagesize = sysconf(_SC_PAGESIZE);
   if(size % pagesize != 0)   
      size = ((size + pagesize) / pagesize) * pagesize;
   /* �ӽй���b����ɤW���x�s�Ŷ��A�䤤�]�A�@�����|����Ϫ��B�~�@�� */
   mem = (void *)valloc(size + pagesize);
   /* �إ߷���O�@�� */
#ifdef STACK_GROWS_UP
   guard_addr = mem + size;
   stack_addr = mem;
#else
   guard_addr = mem;
   stack_addr = mem + pagesize;
#endif
   if (mprotect(guard_addr, pagesize, PROT_NONE))
      err_exit("mprotect");
   printf("stack area=(%d,%d)\n", stack_addr, stack_addr+size-1);
   printf("gaurded area=(%d,%d)\n", guard_addr, guard_addr+pagesize-1);
   return stack_addr;
}
int main (void)
{
   pthread_t thread;
   int rv;
   pthread_attr_t attr;
   size_t stacksize, guardsize;
   char *stackaddr;
   pthread_attr_init(&attr);      /* �_�l�ư�����ݩʪ���*/
   /* �ӽХΧ@��������|���Ŷ� */
   stackaddr = (void *)thread_stack_alloc(PTHREAD_STACK_MIN); 
   /* �]�w������ݩʪ��󤤪����|��}�M�j�p */
   rv = pthread_attr_setstack(&attr, stackaddr, PTHREAD_STACK_MIN); 
   check_error(rv, "pthread_setstack()");
   /* �˵����|�ݩʭ� */   
   pthread_attr_getstack(&attr, (void *)&stackaddr, &stacksize);
   pthread_attr_getguardsize(&attr, &guardsize);
   printf("stack attributes: stackaddr=%d, stacksize=%d, guardsize=%d\n", 
           stackaddr, stacksize, guardsize);
   /* �إ߰���� */
   rv = pthread_create(&thread, &attr, (void *(*)())Hello, (void *)NULL);
   check_error(rv, "pthread_create()");
   pthread_attr_destroy(&attr);   /* �ήɾP��������ݩʪ���A�קK�A���ϥ� */
   check_error(rv, "pthread_attr_destroy()");
   /* ... ���~�{���{���X ... */
   pthread_exit(NULL);
}
