//semshm_s.c        生产者
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include "semshm.h"

int main()
{
    int empty,full,shmid;
    empty=semget(SEM_KEY_1,1,0);        //获得信号量
    full=semget(SEM_KEY_2,1,0);
    shmid=shmget(SHM_KEY,0,0);      //获得共享内存
    if(empty==-1||full==-1||shmid==-1)
    {
        perror("get");
        exit(-1);
    }

    struct msg_data *buf;
    void * tmp=shmat(shmid,NULL,0);     //映射共享内存
    buf=(struct msg_data*)tmp;
    int i=0;
    for(i=0;i<5;i++)
    {
        sleep(1);
        P(empty);      
        Productor(buf,i);       //生产者向共享内存写入数据
        V(full);
    }
    return 0;
}