#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
struct any{
    char buffer[100];
};
int main(){
    int shmid=shmget((key_t)1234,sizeof(struct any),0666|IPC_CREAT);
    if(shmid==-1){
        printf("failed shmid\n");
        return 0;
    }
    void *s=shmat(shmid,(void*)0,0);
    if(s==(void*)-1){
        printf("falided shmat\n");
        return 0;
    }
    struct any *shared=(struct any*)s;
    char buff[100];
    while(1){
        printf("\nEnter the text you want to save: ");
        fgets(buff,sizeof(buff),stdin);
        printf("the entered text is %s\n",buff);
        strcpy(shared->buffer,buff);
    }
}