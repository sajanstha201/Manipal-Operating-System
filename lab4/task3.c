#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
typedef struct{
    int size;
    int *arr;
    int odd_number,even_number;
} DATA;
void * odd_thread(void *z){
    DATA *data=z;
    data->odd_number=0;
    int i;
    for(i=0;i<data->size;i++)
        if(data->arr[i]%2==0)
            data->odd_number+=1;
}
void * even_thread(void *z){
    DATA *data=z;
    data->even_number=0;
    int i;
    for(i=0;i<data->size;i++)
        if(data->arr[i]%2!=0)
            data->even_number+=1;
}
void main(){
    DATA data;
    printf("Enter the size of array: ");
    scanf("%d",&data.size);
    int i;
    data.arr=(int*)malloc(sizeof(int)*data.size);
    for(i=0;i<data.size;i++){
        scanf("%d",&data.arr[i]);
    }
    pthread_t oddThread,evenThread;
    pthread_create(&oddThread,NULL,odd_thread,&data);
    pthread_create(&evenThread,NULL,even_thread,&data);
    pthread_join(oddThread,NULL);
    pthread_join(evenThread,NULL);
    printf("The number of even number is %d\nThe number of odd number is %d\n",data.even_number,data.odd_number);
}