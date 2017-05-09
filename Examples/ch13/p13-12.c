#include "ch13.h"
extern struct job *create_job();            //�إߤ@�ӧ@�~
extern void job_enqueue(struct job *ptr); //�V�@�~��C�[�J�@�ӧ@�~
typedef struct job_sync_data {
   int job_count;            //�@�~��
   pthread_mutex_t mtx;     //�Ω�O�@job_count
   pthread_cond_t cond;     //�Ω󪾷|job_count������
} job_sync_data;
extern job_sync_data job_sync;
void master_thread()
{
   struct job *new_job;
   int rv;
   for (; ;) {
      if ((new_job = create_job())== NULL)  // �إߤU�@�ӧ@�~
         pthread_exit((void *)NULL);         // �S���i�@�B���u�@�h�פ�ۤv
      /* ��o�۳s�������ܼ� */
      rv=pthread_mutex_lock(&job_sync.mtx); 
      check_error(rv, "mutex lock");
      /* �[�J�s�@�~�ܧ@�~��C */
      job_enqueue(new_job);
      job_sync.job_count++;
      /* �V�����ܼƵo�T������@�Ӱ���� */
      rv = pthread_cond_signal(&job_sync.cond);
      check_error(rv,"cond_signal");  
      /* ����۳s�������ܼ� */
      rv=pthread_mutex_unlock(&job_sync.mtx);
      check_error(rv,"mtx_unlock");
   }
}
