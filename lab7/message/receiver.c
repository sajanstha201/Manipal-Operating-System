#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
struct msg_t{
    char text[100];
};
int main(){
    int msgid=msgget((key_t)1234,0666|IPC_CREAT);
    struct msg_t some_m;
    int running=1;
    while(running){
        if(msgrcv(msgid,(void*)&some_m,100,0,0)==-1){
            printf("error\n");
        }
        printf("your text is %s\n",some_m.text);
        if(strncmp(some_m.text,"stop",4)==0){
            running=0;
        }
    }
}