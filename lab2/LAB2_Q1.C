#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int pid;
	int status;
	pid = fork();
	if(pid < 0){
		printf("ERROR");
		exit(0);
	}
	else if(pid == 0){
		printf("\nTHIS IS THE CHILD PROCESS ");
		printf("\n THE PID IS : %d \n",getpid());
		printf("MY PARENT PID IS : %d\n",getppid());
		exit(0);
	}
	else{
		wait(&status);
		printf("\nTHIS IS THE PARENT PROCESS ");
		printf("\n THE PID IS : %d \n",getpid());
		printf("MY PARENT PID IS : %d\n",getppid());
		exit(0);
	}
}
