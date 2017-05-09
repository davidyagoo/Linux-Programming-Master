/* P�ʧ@--���϶i�J�@����� */
void semaphore_P(int sem_id)
{
   struct sembuf sb;
   sb.sem_num = 0;
   sb.sem_op = -1;          /* P�ʧ@�аT���q�ȴ�� */
   sb.sem_flg = SEM_UNDO;   /* �Y�G���`�A�Ѱ��T���q�ШD*/
   if (semop(sem_id, &sb, 1) == -1){
       fprintf(stderr,��semaphore_P failed\n��);
       return(0);
   }
   return(1);
}
/* V�ʧ@--���}����� */
void semaphore_V(int sem_id)
{
   struct sembuf sb;
   sb.sem_num = 0;
   sb.sem_op = 1;           /* V�ʧ@�аT���q�ȼW�[ */
   sb.sem_flg = SEM_UNDO;   /* �Y�G���`�A�Ѱ��T���q�ШD*/
   if (semop(sem_id, &sb, 1) == -1){
       fprintf(stderr,��semaphore_V failed\n��);
       return(0);
   }
   return(1);
}
