#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#define BUFFERSIZE 100
struct shm{
    int who;
    char text[BUFFERSIZE];
    char ch;
};
int main(){
    int shmid=shmget((key_t)1234,sizeof(struct shm),0666|IPC_CREAT);
    void *s=shmat(shmid,(void*)0,0);
    struct shm *shared=(struct shm*)s;
    int pid=fork();
    if(pid==0){
        int running=1;
        shared->who=1;
        while(running){
            while(shared->who==1){
                sleep(1);
            }
            int nextchar=shared->ch+1;
            shared->ch=nextchar;
            shared->who=1;
        }
    }
    else if(pid>0){
        int running=1;
        shared->who=1;
        while(running){
            printf("Enter a character: ");
            int ch;
            scanf(" %c",&ch);
            shared->ch=ch;
            shared->who=0;
            while(shared->who==0){
                sleep(1);
            }
            printf("The next character is %c\n",shared->ch);
        }


    }
}