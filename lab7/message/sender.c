#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
struct meg{
    char text[100];
};
int main(){
    struct meg some_msg;
    int msgid=msgget((key_t)1234,0666|IPC_CREAT);
    int running=1;
    while(running){
        printf("Enter a text: ");
        char buffer[100];
        fgets(buffer,100,stdin);
        strncpy(some_msg.text,buffer,100);
        msgsnd(msgid,(void*)&some_msg,100,0);
        if(strncmp(buffer,"stop",4)==0){
            running=0;
        }
    }
}