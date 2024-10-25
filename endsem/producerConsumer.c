#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
pthread_mutex_t mutex;
pthread_cond_t producer_cond=PTHREAD_COND_INITIALIZER;
pthread_cond_t consumer_cond=PTHREAD_COND_INITIALIZER;
#define MAX 10
sem_t empty=5,full=MAX-5;
int queue[MAX];
int k=-1;
void enqueue(int n){
    queue[++k]=n;
}
int dequeue(){
    return queue[k--];
}
void printC(){
    int i;
    printf("Storage: ");
    for(i=0;i<=k;i++){
        printf("%d ",queue[i]);
    }
    printf("\n");
}
void *producer(void * arg){
    sem_wait(&full);
    // pthread_mutex_lock(&mutex);
    sem_post(&empty);
    int item=rand()%100;
    printf("Produced: %d\n",item);
    enqueue(item);
    printC();
    // pthread_mutex_unlock(&mutex);
}
void *consumer(void *arg){
    int j;
    for(j=0;j<1000000;j++);
    sem_wait(&empty);
    // pthread_mutex_lock(&mutex);
    sem_post(&full);
    printf("Consumed: %d\n",dequeue());
    printC();
    // pthread_mutex_unlock(&mutex);
}

int main(){
    int i,j;
    pthread_t cthread[10],pthread[10];
    for(i=0;i<10;i++){
        pthread_mutex_init(&mutex,NULL);
        pthread_create(&cthread[i],NULL,producer,0);
        pthread_create(&pthread[i],NULL,consumer,0);
    }
    for(i=0;i<10;i++){
        pthread_join(cthread[i],NULL);
        pthread_join(pthread[i],NULL);
    }

}