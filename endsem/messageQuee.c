#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>
#include<time.h>
struct m{
    int n,h,m;
};
int main(){
    int msgid=msgget((key_t)12345,0666|IPC_CREAT);
    // printf("Enter any numebr to start\n");
    // int n;
    // scanf("%d",&n);
    time_t t;
    while(1){
        time(&t);
        struct tm* l_time=localtime(&t);
        int s=l_time->tm_sec;
        int prev;
        if(s%5==0){
            if(prev==s)
                continue;
            
            struct m message1;
            message1.n=rand()%100;
            message1.h=l_time->tm_hour;
            message1.m=s;
            printf("%d \n",message1.n);
            msgsnd(msgid,(void*)&message1,sizeof(struct m),0);
            printf("message sent\n");
            prev=s;
        }
    }
}