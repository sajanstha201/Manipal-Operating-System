#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdbool.h>
#include<stdlib.h>
struct PrimeStruct{
    int start,end;
    int *arr;
    int count;
};
bool isPrime(int n){
    int i;
    for(i=2;i<n;i++){
        if(n%i==0)
            return false;
    }
    return true;
}
void * findPrimeNumber(void *z){
    struct PrimeStruct *data=z;
    int i;
    data->arr=(int*)malloc(sizeof(int)*(data->end-data->start+1));
    for(i=data->start;i<=data->end;i++){
        if(isPrime(i)){
            data->arr[data->count]=i;
            data->count+=1;
        }
    }
}
void main(){
    int i,start,end;
    struct PrimeStruct primeData;
    printf("Enter the starting point: ");
    scanf("%d",&primeData.start);
    printf("Enter the ending point: ");
    scanf("%d",&primeData.end);
    primeData.count=0;
    pthread_t prime_thread;
    pthread_create(&prime_thread,NULL,findPrimeNumber,&primeData);
    pthread_join(prime_thread,NULL);
    printf("The prime number between %d and %d are: \n",primeData.start,primeData.end);
    for(i=0;i<primeData.count;i++){
        printf("%d, ",primeData.arr[i]);
    }
}