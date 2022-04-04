//semshm.h      封装了创建信号量删除信号量，以及生产操作和消费操作
#ifndef SEMSHM_H
#define SEMSHM_H

#define SHM_KEY 9494
#define SEM_KEY_1 9399
#define SEM_KEY_2 9595
#define BUF_SIZE 1024
#include <string.h>

union semnum
{
    int     val;
    struct semid_ds *buf;
    unsigned short  *array;
};

int sem_create(key_t key,int val)       //创建一个信号量并置初值为val
{
    int semid;
    semid=semget(key,1,0666|IPC_CREAT);
    if(semid==-1)
    {
        perror("semget");
        exit(-1);
    }
    union semnum arg;       //联合类型的变量初始化必须用{}，赋值使用 arg.val=0
    arg.val=val;        //设信号量的初始值
    if(semctl(semid,0,SETVAL,arg)==-1)
    {
        perror("semctl");
        exit(-1);
    }
    return semid;
}

void sem_del(int semid)     //删除信号量
{
    union semnum arg;
    arg.val=0;
    if(semctl(semid,0,IPC_RMID,arg)==-1)
    {
        perror("semctl");
        exit(-1);
    }
}

int P(int semid)        //P操作，使信号量的值减1
{
    struct sembuf sops={0,-1,SEM_UNDO};     //第三个参数设置为SEM_UNDO时当信号量小于0时会阻塞，设置为IPC_NOWAIT则不会阻塞
    return (semop(semid,&sops,1));
    
}

int V(int semid)        //V操作，使信号量的值加1
{
    struct sembuf sops={0,+1,SEM_UNDO};
    return (semop(semid,&sops,1));
}

struct msg_data     //定义一个共享内存存储的消息结构体
{
    char data[BUF_SIZE];
};

void Productor(struct msg_data *msg,int i)      //生产者
{
    const char * str="productid:";
    char *array[]={"1","2","3","4","5"};
    strcpy(msg->data,str);
    strcat(msg->data,array[i]);
    printf("Productor:%s\n",msg->data);
}

void Customer(struct msg_data *msg)     //消费者
{
    printf("Customer:%s\n",msg->data);
}
#endif