#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
char buffer[100];
pthread_mutex_t mutex;
void *reader(void *arg){
    pthread_mutex_lock(&mutex);
    printf("Read: %s\n",buffer);
    pthread_mutex_unlock(&mutex);
}
void *writer(void *arg){
    pthread_mutex_lock(&mutex);
    printf("Enter a word to write: ");
    fgets(buffer,sizeof(buffer),stdin);
    pthread_mutex_unlock(&mutex);
    int i;
    for(i=0;i<1000000;i++);
}
int main(){
    pthread_mutex_init(&mutex,NULL);
    pthread_t r[5],w[5];
    int i;
    for(i=0;i<5;i++){
        pthread_create(&w[i],NULL,writer,0);
        pthread_create(&r[i],NULL,reader,0);
    }
    for(i=0;i<5;i++){
        pthread_join(r[i],NULL);
        pthread_join(w[i],NULL);
    }
}