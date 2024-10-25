#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
pthread_mutex_t mutex;
char buffer[100];
void *reader(void * arg){
    pthread_mutex_lock(&mutex);
    printf("Read: %s\n",buffer);
    pthread_mutex_unlock(&mutex);
}
void *writer(void *arg){
    pthread_mutex_lock(&mutex);
    printf("Enter a string: ");
    fgets(buffer,sizeof(buffer),stdin);
    pthread_mutex_unlock(&mutex);
}
int main(){
    pthread_mutex_init(&mutex,NULL);
    int n=10,i;
    pthread_t w[n],r[n];
    for(i=0;i<n;i++){
        pthread_create(&w[i],NULL,writer,0);
        pthread_create(&r[i],NULL,reader,0);
    }
    for(i=0;i<n;i++){
        pthread_join(w[i],NULL);
        pthread_join(r[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
}