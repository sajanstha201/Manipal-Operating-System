#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
struct shm_st{
    int flag;
    char text[100];
};
int main(){
    int shmid=shmget((key_t)1234,sizeof(struct shm_st),0666|IPC_CREAT);
    void *shm_a=shmat(shmid,(void *)0,0);
    struct shm_st *shared=(struct shm_st*)shm_a;
    int running=1;
    while(running){
        while(shared->flag==1){
            sleep(1);
            printf("Waiting...");
        }
        printf("Enter a text: ");
        char buffer[100];
        fgets(buffer,100,stdin);
        shared->flag=1;
        strncpy(shared->text,buffer,100);
        if(strncmp(buffer,"stop",4)==0){
            running=0;
        }
    }
}
