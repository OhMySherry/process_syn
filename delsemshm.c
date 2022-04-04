//delsemshm.c  //删除所建的信号量和共享内存
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "semshm.h"

int main()
{
    int empty,full,shmid;
    empty=semget(SEM_KEY_1,1,0);
    full=semget(SEM_KEY_2,1,0);
    shmid=shmget(SHM_KEY,0,0);
    if(empty==-1||full==-1||shmid==-1)
    {
        perror("del get");
        exit(-1);
    }
    sem_del(empty);
    sem_del(full);
    struct shmid_ds *ds=(struct shmid_ds*)malloc(sizeof(struct shmid_ds));
    shmctl(shmid,IPC_RMID,ds);
    printf("del success !\n");
    return 0;
}