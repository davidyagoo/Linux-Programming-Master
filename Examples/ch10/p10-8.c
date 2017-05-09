#include "ch10.h"
#define NBUFFERS 2            /* �w�R�ϭӼ� */
#define BUFFERSIZE 2048       /* �w�R�Ϥj�p */
#define BLOCKSIZE  1024       /* �C��Ū�J����ư϶��j�p */
#define SIG_AIO_WRITE (SIGRTMIN+5)

typedef enum {BUFFER_FREE=1,BUFFER_FILLING,BUFFER_WRITING} BUFFLAG;
typedef struct {
   BUFFLAG state;              /* �w�R�Ϫ��A */
   int fillpt;                 /* �w�R�Ϥ��̫�@�Ӹ�Ʀ�m */
   struct aiocb acb;           /* ���B��X����� */
   char buffer [BUFFERSIZE];   /* ��ƽw�R�� */
} buffer_t;
static buffer_t buf_list[NBUFFERS];
static sigset_t aio_completion_signal;
static volatile int sigcnt = 0, total = 0;
static off_t seek_ptr;

/* ���B��X�����T������X */
void aio_ok(int signo, siginfo_t *info, void *ignored)
{
   buffer_t *donebuf;
   ssize_t rval;
   if ((signo != SIG_AIO_WRITE)||info->si_code!=SI_ASYNCIO)
      return; // �DAIO�����T��   
   else
      printf("AIO write completed\n");
/* �ھ�info��o���BI/O���p���T���C */
   donebuf = (buffer_t *)info->si_value.sival_ptr;
   if ((aio_error((struct aiocb *) &donebuf->acb) != EINPROGRESS))
      rval=aio_return((struct aiocb *) &donebuf->acb);
/* �֭p�g�X���줸�ռƩM�T���o�ͦ��ơA�üХܽw�R�Ϥw��*/
   total += rval; sigcnt++;
   donebuf->state = BUFFER_FREE;
   donebuf->fillpt = 0;
   return;
}
buffer_t *find_free_buf (void) /* ��o�@�Ӷ��m���w�R�� */
{
   int i;
   sigset_t prevmask;
   sigprocmask(SIG_BLOCK, &aio_completion_signal, &prevmask);
   while (1) {
      for (i=0; i<NBUFFERS; i++) {
         if (buf_list[i].state == BUFFER_FREE)
            break;
      }
      if (i == NBUFFERS) 
         sigsuspend(&prevmask);  /* �S�����m�w�R�ϡA���ݬY�Ӳ��B��X�����᭫�աC*/
      else
         break;
   }
   buf_list[i].state = BUFFER_FILLING; /* ���F���m�w�R�ϡA�Чӥ����Q�ϥ� */
   buf_list[i].fillpt = 0;
   sigprocmask(SIG_SETMASK, &prevmask, NULL);
   return (&buf_list[i]);
}
void flush_filled_buf(buffer_t *full_guy) /* �g�X�w�R�Ϥ������ */
{
   /* �]�w AIOCB */
   full_guy->acb.aio_offset = seek_ptr;
   seek_ptr += full_guy->fillpt;
   full_guy->acb.aio_buf = full_guy->buffer;
   full_guy->acb.aio_nbytes = full_guy->fillpt;
   full_guy->acb.aio_reqprio = 0;
   full_guy->acb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
   full_guy->acb.aio_sigevent.sigev_signo = SIG_AIO_WRITE;
   full_guy->acb. aio_sigevent.sigev_value.sival_ptr = (void *)full_guy;
   full_guy->state = BUFFER_WRITING; /* �Чӽw�R�Ϫ��A�����b�g�X*/  
   if (aio_write(&full_guy->acb) < 0) /* �o�X���B��X�ШD */
      perror ( "aio_write" ) ;
   return;
}
main(int argc, char **argv)
{
   int  i, in_file, out_file;
   buffer_t *currentbuf;
   struct sigaction sig_act;
   int chunksize;
   if (argc != 4) {/* �ˬd�ѼƭӼ� */
      fprintf(stderr, "Usage: %s input-file output-file buf-size-in-Kb\n",
               argv[0]);
      exit(0);
   }
   /* �}�ҿ�J�M��X�ɮ� */
   if ((in_file = open(argv[1], O_RDONLY)) == -1) 
      err_exit(argv[1]);
   if ((out_file = open(argv[2], O_WRONLY|O_CREAT, 0777)) == -1)
      err_exit(argv[2]);
   chunksize=atol(argv[3])*BLOCKSIZE;
    /* �_�l�w�R�Ϫ��A�ä��t�@�ӽƻs�ɮת��w�R�� */
   for (i=0; i<NBUFFERS; i++){
      buf_list[i].acb.aio_fildes = out_file;
      buf_list[i].state = BUFFER_FREE;
      buf_list[i].fillpt = 0;
   }
   currentbuf = find_free_buf();
	   /* �إ߲��BI/O�����T������X */
   sigemptyset(&aio_completion_signal);
   sigaddset(&aio_completion_signal, SIG_AIO_WRITE);
   sigemptyset(&sig_act.sa_mask);                  
   sig_act.sa_flags = SA_SIGINFO;
   sig_act.sa_sigaction = aio_ok;
   if (sigaction (SIG_AIO_WRITE, &sig_act, 0) < 0)
      perror("sigaction");
	   /* �qin_file�ƻs�ɮר�out_file */
   while (1) {
      int nbytes;
again:
      /* Ū�@���T���ܽw�R�� */
      nbytes = read(in_file, currentbuf->buffer+currentbuf->fillpt, 
                      chunksize);
      if (nbytes>0) {
         currentbuf->fillpt += nbytes;
         if (currentbuf->fillpt == BUFFERSIZE) {
            /* �g�X�w�����w�R�Ϩ���o�@�ӷs�w�R�� */
            flush_filled_buf (currentbuf);
            currentbuf = find_free_buf() ;
         }
      } else if (nbytes == 0) { /* ��F�ɮק� */
         flush_filled_buf (currentbuf);
         break;
      } else {                  
         if (errno == EINTR) goto again;  /* �Q�T�����_�A���sŪ */
         else err_exit("read");
      }
   }
   for (i=0; i<NBUFFERS; i++){  /* ���ݩҦ����B��X���� */
      if (buf_list[i].state == BUFFER_WRITING){
         struct aiocb *acbp[1];
         acbp[0] = &buf_list[i].acb;
         aio_suspend(acbp, 1, NULL);
      }
   }
   close(in_file);
   close(out_file);
   printf("Copied: %d bytes, %d signals taken\n", total, sigcnt);
}
