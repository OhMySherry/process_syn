//allsemshm.c       创建了2个信号量用于实现生产者和消费者之间的同步问题，并创建了一个共享内存作为共享资源
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
    empty=sem_create(SEM_KEY_1,1);      //设置一个信号量置初值为1
    full=sem_create(SEM_KEY_2,0);       //设置一个信号量置初值为0
    shmid=shmget(SHM_KEY,sizeof(struct msg_data),0666|IPC_CREAT);
    if(shmid==-1)
    {
        perror("shmget");
        exit(-1);
    }

    printf("empty=%d\tfull=%d\tshmid=%d\n",empty,full,shmid);
    return 0;
}
