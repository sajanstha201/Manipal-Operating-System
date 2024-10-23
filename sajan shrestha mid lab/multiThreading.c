#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
struct prime{
    int starting,ending;
};
int checkPrime(int n){
    int i;
    for(i=2;i<n;i++)
        if(n%i==0)
            return 0;
    return 1;
}
void *runner(void* arg){
    struct prime *p=arg;
    int i;
    printf("The prime number between %d and %d are: \n",p->starting,p->ending);
    for(i=p->starting;i<=p->ending;i++){
        if(checkPrime(i)){
            printf("%d ",i);
        }
    }
}
int main(){
    pthread_t thread;
    printf("Enter the starting point: ");
    struct prime p;
    scanf("%d",&p.starting);
    printf("Enter the ending point: ");
    scanf("%d",&p.ending);
    pthread_create(&thread,NULL,runner,&p);
    pthread_join(thread,NULL);
}