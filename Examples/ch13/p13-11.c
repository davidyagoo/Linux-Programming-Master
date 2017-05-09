#include "ch13.h"
typedef struct job_sync_data {
   int job_count;            //�@�~��
   pthread_mutex_t mtx;     //�Ω�O�@job_count
   pthread_cond_t cond;     //�Ω󪾷|job_count������
} job_sync_data; 
job_sync_data job_sync = {
              0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};
struct job {
   int job_id;
   void * work_ptr;
};
extern struct job *job_dequeue();          //�q�@�~��C�����R�@�ӧ@�~
extern void procee_job(struct job *ptr);  //�B�z�@�ӧ@�~
void worker_thread()
{
   struct job *curr_job;
   int rv;
   for(; ;){
      /* ��o�����ܼƬ۳s�������ܼ� */
      rv=pthread_mutex_lock(&job_sync.mtx);  
      check_error(rv, "mutex lock");
      /* ���զ��_�@�~�A�Y�G�S���h���ݡC�����ܼƵ��ݷ|����۳s�������ܼƥH�K�䥦�����
         �����m�@�~���C�����C�q�����ܼƵ��ݶǦ^���e�|���s��o�Ӥ����ܼ� */
      while (job_sync.job_count == 0)
         pthread_cond_wait(&job_sync.cond, &job_sync.mtx);
      curr_job=job_dequeue(); // �o��@�~
      if (curr_job != NULL) 
         job_sync.job_count--; 
      // ����۳s�������ܼ�
      rv=pthread_mutex_unlock(&job_sync.mtx);
      check_error(rv, "mtx_unlock failed");
      // �B�z�@�~
      procee_job(curr_job); 
   }
}
