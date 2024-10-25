#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
int checkPalindrome(int n){
    int temp=n,rev=0,k;
    while(temp!=0){
        k=temp%10;
        temp=(int)temp/10;
        rev=rev*10+k;
    }
    if(rev==n)
        return 1;
    else
        return 0;

}
int main(){
    int msgid=msgget((key_t)1234,0666|IPC_CREAT);
    int pid=fork();
    int status;
    if(pid==0){
        int num;
        printf("This is child process\n");
        printf("Enter a number to check palindrome: ");
        scanf("%d",&num);
        msgsnd(msgid,(void*)&num,sizeof(num),0);
    }
    else{
        wait(&status);
        int num;
        printf("This is parent process\n");
        msgrcv(msgid,(void*)&num,sizeof(num),0,0);
        if(checkPalindrome(num))
            printf("%d is palindrome number\n",num);
        else
            printf("%d is not palindromr number\n",num);
    }
}