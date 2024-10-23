#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define max 5
int x=0;
int full=0, empty=max;
pthread_mutex_t mutex;
pthread_cond_t pcond=PTHREAD_COND_INITIALIZER;
pthread_cond_t ccond=PTHREAD_COND_INITIALIZER;
void waits(int *sem){
    while(*sem<=0);
    int c=*sem;
    *sem=c-1;
}
void signals(int *sem){
    int c=*sem;
    *sem=c+1;
}
void* producer(void * arg){
    while(x<=50){
        x++;
        pthread_mutex_lock(&mutex);
        while(empty==0){
            pthread_cond_wait(&pcond,&mutex);
        }
        waits(&empty);
        printf("Produced\n");
        int i;
        // printf("%d %d \n",max,empty);
        for(i=0;i<max-empty;i++)
            printf("%d - ",i);
        printf("\n");
        signals(&full);
        pthread_cond_signal(&ccond);
        pthread_mutex_unlock(&mutex);
    }

    
}
void * consumer(void* arg){
    while(x<50){
        pthread_mutex_lock(&mutex);
        while(full==0){
            pthread_cond_wait(&ccond,&mutex);
        }
        waits(&full);
        printf("Consumed\n");
        int i;
        for(i=0;i<full;i++){
            printf("%d - ",i);
        }
        printf("\n");
        signals(&empty);
        pthread_cond_signal(&pcond);
        pthread_mutex_unlock(&mutex);
    }

}
int main(){
    pthread_t cthread,pthread;
    pthread_create(&cthread,NULL,consumer,NULL);
    pthread_create(&pthread,NULL,producer,NULL);
    pthread_join(pthread,NULL);
    pthread_join(cthread,NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&pcond);
    pthread_cond_destroy(&ccond);
}