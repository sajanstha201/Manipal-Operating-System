#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<sys/msg.h>
struct m{
    int n,h,m;
};
int main(){
    int msgid=msgget((key_t)12345,0666|IPC_CREAT);
    int total_n=0;
    time_t t;
    while (1)
    {
        time(&t);
        struct tm* ti=localtime(&t);
        int s=ti->tm_sec;
            struct m gotmsg;
            msgrcv(msgid,(void*)&gotmsg,sizeof(gotmsg),0,0);
            total_n+=gotmsg.n;
            if(gotmsg.m%20==0){
                printf("The average user is %d\n",total_n);
                total_n=0;
            }
 
    }
    
}