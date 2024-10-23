#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
int main(){
    int msgid=msgget((key_t)1234,0666|IPC_CREAT);
    char buf[100];
    while (1){
        printf("Enter a string: ");
        fgets(buf,sizeof(buf),stdin);
        msgsnd(msgid,(void*)&buf,sizeof(buf),0);
    }
    
}