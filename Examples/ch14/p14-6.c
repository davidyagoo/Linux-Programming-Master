//#include "ch14.h"
struct sched_thread {
   int num;
   int policy;
   int priority;
   void * (*thread_func)();
};

pthread_t create_exlicit_sched_threads(struct sched_thread *arg)
{
   pthread_t tid;
   pthread_attr_t attr;
   struct sched_param param;
   int rv, scope;

   assert(arg->policy==SCHED_FIFO||arg->policy==SCHED_RR);
   /* �_�l�ư�����ݩʪ��� */
   rv = pthread_attr_init(&attr);
   check_error(rv, "attr init");
   /* �]�w������ݩʪ��󤤪�����������~���ݩʬ��D�~�� */
   rv = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
   check_error(rv, "attr_setinheritsched");
   /* �]�w���v���d�򬰨t�νd�� */
   rv = pthread_attr_getscope(&attr, &scope);
   check_error(rv, "attr_ getscope");
   if (scope != PTHREAD_SCOPE_SYSTEM){
      rv = pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
      check_error(rv, "attr_ setscope");
   }
   /* �إߤ@�ӫ��w�����ݩʪ������ */
   rv = pthread_attr_setschedpolicy(&attr, arg->policy);    // �]�w��������
   check_error(rv, "create_exlicit_sched_thread:setschedpolicy");
   param.sched_priority = arg->priority;                   // �]�w�����u����
   rv = pthread_attr_setschedparam(&attr, &param);      
   check_error(rv, "create_exlicit_sched_thread:setschedparam");
   rv = pthread_create(&tid, &attr, arg->thread_func, (void *)arg->num);
   check_error(rv, "create thread 1");
   /* �P��������ݩʪ��� */
   rv = pthread_attr_destroy(&attr);
   check_error(rv, "attr destroy");
   return tid;
}
