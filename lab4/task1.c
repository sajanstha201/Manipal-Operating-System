#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
struct fibData{
    int size;
    int *arr;
};
void *fibCreation(void *z){
    struct fibData *data=z;
    int i,a=0,b=1,temp;
    data->arr=(int*)malloc(4*data->size);
    for(i=0;i<data->size;i++){
        data->arr[i]=a;
        temp=a+b;
        a=b;
        b=temp;
    }
    return 0;
}
int main( ){
    int n,i;
    struct fibData data;
    printf("Enter the total number of sequence\n");
    scanf("%d",&data.size);
    pthread_t fib_thread;
    pthread_create(&fib_thread,NULL,&fibCreation,&data);
    pthread_join(fib_thread,NULL);
    for(i=0;i<data.size;i++)
        printf("%d, ",data.arr[i]);
}