#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
#include<pthread.h>
#define max 10
sem_t full,empty;
pthread_mutex_t mutex;
int f=0;
void *consumer(void* arg){
    int i;
    for(i=0;i<1000000;i++);
    sem_wait(&full);
    sem_post(&empty);
    pthread_mutex_lock(&mutex);
    printf("consumed\n");
    f--;
    printf("storage %d\n",f);
    pthread_mutex_unlock(&mutex);
}
void *producer(void* arg){
    int i;
    sem_wait(&empty);
    sem_post(&full);
    pthread_mutex_lock(&mutex);
    printf("produced\n");
    f++;
    printf("storage %d\n",f);
    pthread_mutex_unlock(&mutex);
}
int main(){
    pthread_t c[10],p[10];
    sem_init(&full,0,0);
    sem_init(&empty,0,10);
    pthread_mutex_init(&mutex,NULL);
    int i;
    for(i=0;i<10;i++){
        pthread_create(&p[i],NULL,producer,0);
        pthread_create(&c[i],NULL,consumer,0);
    }
    for(i=0;i<10;i++){
        pthread_join(p[i],NULL);
        pthread_join(c[i],NULL);
    }
    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);
}