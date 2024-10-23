#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int max=0;
#define BUFFERSIZE 3
int full=0,empty=BUFFERSIZE-1,target=0;

void waits(int *sem){
    while(*sem<=0);
    int c=*sem;
    *sem=c-1;
}
void signals(int *sem){
    int c=*sem;
    *sem=c+1;
}
// void acquire(int *target){
//     while(*target==1){
//         printf("watiig for release\n");
//     }
//     *target=1;
// }
// void release(int* target){
//     *target=0;
// }
pthread_mutex_t mutex;
pthread_cond_t cond_producer=PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_consumer=PTHREAD_COND_INITIALIZER;
void *producer(void *n){
    int i;
    while(max<=10){
        max++;
        pthread_mutex_lock(&mutex);
        while(full==BUFFERSIZE){
            pthread_cond_wait(&cond_producer,&mutex);
        }
        waits(&empty);
        signals(&full);
        pthread_cond_signal(&cond_consumer);
        pthread_mutex_unlock(&mutex);
        printf("Produced : ");
        for(i=0;i<full+1;i++) 
        printf("%d",i+1);
        printf("\n");
    }
}
void *consumer(void *n){
    int i;
    while(max<=10){
        pthread_mutex_lock(&mutex);
        while(full==0){
            pthread_cond_wait(&cond_consumer,&mutex);
        }
        waits(&full);
        signals(&empty);
        pthread_cond_signal(&cond_producer);
        pthread_mutex_unlock(&mutex); 
        printf("Consumed : ");
        for(i=0;i<full;i++) 
            printf("%d",i+1);
        printf("\n");
    }

}

int main(){
    pthread_t p_thread,c_thread;
    pthread_create(&p_thread,NULL,producer,NULL);
    pthread_create(&c_thread,NULL,consumer,NULL);
    pthread_join(p_thread,NULL);
    pthread_join(c_thread,NULL);
    pthread_mutex_destroy(&mutex);
}