#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
struct shared_st{
    int written;
    int message[100];
};
int main(){
    int running=1;
    int shmid=shmget((key_t)1234,sizeof(struct shared_st),0666|IPC_CREAT);
    void *shm_addr=shmat(shmid,(void*)0,0);
    struct shared_st *shared_arr=(struct shared_st*)shm_addr;
    while(running){
        while(shared_arr->written==1){
            sleep(1);
            printf("waiting for client...\n");
        }
        printf("Enter teh text:\n");
        char buffer[100];
        fgets(buffer,100,stdin);
        strncpy(shared_arr->message,buffer,100);
        shared_arr->written=1;
        if(strncmp(buffer,"stop",4)==0){
            running=0;
        }
    }

}
