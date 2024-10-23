#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
struct any{
    char *buffer;
};
int main(){
    int shmid=shmget((key_t)123,sizeof(struct any),0666|IPC_CREAT);
    void *s=shmat(shmid,(void*)0,0);
    struct any *shared=s;
    int a;
    while(1){
        printf("the shared memroy value is %s\n",shared->buffer);
        scanf("%d",&a);
    }
}