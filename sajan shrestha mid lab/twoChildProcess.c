#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void bubbleSort(int n,int arr[n]){
    int i,j,k;
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                k=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=k;
            }
        }
    }
    printf("The sorted array is: \n");
    for(i=0;i<n;i++)
        printf("%d ",arr[i]);
    printf("\n");
}
void selectionSort(int n,int arr[n]){
    int i,j,k;
    for(i=0;i<n;i++){
        k=i;
        for(j=i+1;j<n;j++){
            if(arr[k]>arr[j])
                k=j;
        }
        int temp=arr[k];
        arr[k]=arr[i];
        arr[i]=temp;
    }
    printf("The sorted array is: \n");
    for(i=0;i<n;i++)
        printf("%d ",arr[i]);
    printf("\n");
}
int main(){
    int status,n;
    printf("Enter the number of element: ");
    scanf("%d",&n);
    int i,arr[n];
    printf("Enter the array element:\n");
    for(i=0;i<n;i++)
        scanf("%d",&arr[i]);
    int pid=fork();
    if(pid==0){
        printf("This is first Child Process with pid: %d\n",getpid());
        selectionSort(n,arr);
    }
    else if(pid>0){
        wait(&status);
        int newPid=fork();
        if(newPid==0){
            printf("This is second Child Process with pid: %d\n",getpid());
            bubbleSort(n,arr);
        }
        else if(newPid>0){
            wait(&status);
            printf("This is parent Process with pid: %d\n",getpid());
        }
    }
}