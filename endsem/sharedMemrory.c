#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
struct any{
    int flag;
    char buff[100];
};
int main(){
    int shmid=shmget((key_t)1234,sizeof(struct any),0666|IPC_CREAT);
    void *s=shmat(shmid,(void*)0,0);
    struct any *shared=(struct any*)s;
    if(shmid==-1)
        printf("failed shmid");
    if(s==(void*)-1)
        printf("falid shmat");
    char buff[100];
    int pid=fork();
    if(pid==0){
        while (1){
            while(shared->flag==0);
            printf("Enter a string: ");
            fgets(buff,sizeof(buff),stdin);
            strcpy(shared->buff,buff);
            shared->flag=0;
        }
    }
    else{
        while (1) {
            while(shared->flag==1);
            printf("The changed string: %s\n",shared->buff);
            shared->flag=1;
        }
        
    }
    shmdt(shared);
    shmctl(shmid,IPC_RMID,0);
}