#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
struct process{
    int id,arrival_time,brust_time,remaining_time;
};
void printP(int n,struct process p[n]){
    int i;
    for(i=0;i<n;i++){
        printf("%d->%d\n",p[i].id,p[i].remaining_time);
    }
}
int findSJ(int n,struct process p[n],int clock){
    int i;
    int shortest=-1;
    for(i=0;i<n;i++){
        if(p[i].remaining_time>0&&clock>=p[i].arrival_time){
            shortest=i;
        }
            
    }
    if(shortest==-1)
        return -1;
    for(i=0;i<n;i++){
        if(clock>=p[i].arrival_time&&p[i].remaining_time>0&&p[i].remaining_time<p[shortest].remaining_time){
            shortest=i;
        }
    }
    return shortest;
}
int checkCompletion(int n,struct process p[n]){
    int i,j=0;
    for(i=0;i<n;i++){
        if(p[i].remaining_time==0)
            j++;
    }
    if(j==i)
        return 1;
    return 0;
}
int main(){
    int n,i;
    printf("Enter the total number of process: ");
    scanf("%d",&n);
    struct process p[n];
    printf("Enter the arrival time for each process: ");
    for(i=0;i<n;i++)
        scanf("%d",&p[i].arrival_time);
    printf("Enter the brust time for each process: ");
    for(i=0;i<n;i++)
        scanf("%d",&p[i].brust_time);
    for(i=0;i<n;i++){
        p[i].id=i;
        p[i].remaining_time=p[i].brust_time;
    }
    int clock=0;
    while(1){
        int shortest=findSJ(n,p,clock);
        if(shortest==-1)
            break;
        printf("%d ",shortest);
        p[shortest].remaining_time--;
        clock++;
    }
}