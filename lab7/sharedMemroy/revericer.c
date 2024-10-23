#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
struct shared_st{
    int written;
    int message[100];
};
int main(){
    int shmid=shmget((key_t)1234,sizeof(struct shared_st),0666|IPC_CREAT);
    void *shm_addr=shmat(shmid,(void*)0,0);
    struct shared_st *shared_addr=(struct shared_st*)shm_addr;
    int running=1;
    shared_addr->written=0;
    while(running){
        if(shared_addr->written){
            printf("The entered datais %s\n",shared_addr->message);
        }
        shared_addr->written=0;
        if(strncmp(shared_addr->message,"stop",4)==0){
            running=0;
        }
        sleep(1);
    }
}