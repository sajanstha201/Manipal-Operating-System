#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
struct any{
    char buffer[100];
};
int main(){
    int shmid=shmget((key_t)123,sizeof(struct any),0666|IPC_CREAT);
    void *s=shmat(shmid,(void*)0,0);
    struct any *shared=(struct any*)s;
    int a;
    printf("sjan shrjf");
    while(1){
        scanf("%d",&a);
        printf("the shared memroy value is %s\n",shared->buffer);
        
    }
}