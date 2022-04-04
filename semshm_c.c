//semshm_c.c        消费者
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
    empty=semget(SEM_KEY_1,1,0);        //获取信号量
    full=semget(SEM_KEY_2,1,0);
    shmid=shmget(SHM_KEY,0,0);      //获取共享内存
    if(empty==-1||full==-1||shmid==-1)
    {
        perror("get");
        exit(-1);
    }

    struct msg_data *buf;
    buf=(struct msg_data*)shmat(shmid,NULL,0);      //映射共享内存地址
    int i=0;
    for(i=0;i<5;i++)
    {
        P(full);
        Customer(buf);      //消费者从共享内存取数据
        V(empty);
    }
    return 0;
}