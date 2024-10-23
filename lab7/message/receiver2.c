#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
int main(){
    int msgid=msgget((key_t)1234,0666|IPC_CREAT);
    char buff[100];
    while (1)
    {
        msgrcv(msgid,(void*)&buff,sizeof(buff),0,0);
        printf("The received message is %s\n",buff);
    }
    
}