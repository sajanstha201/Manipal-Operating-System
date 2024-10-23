#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
typedef struct {
    int pid;
    int arrival_time,burst_time;
    int waiting_time;
    int remaining_time;
} PROCESS;
int main(){
    int i,j,k,n;
    printf("Enter the number of process: ");
    scanf("%d",&n);
    PROCESS p_arr[n];
    for(i=0;i<n;i++){
        // printf("PID for %d process: ",i+1);
        // scanf("%d",&p_arr[i].pid);
        printf("Arrival Time for %d process: ",i+1);
        scanf("%d",&p_arr[i].arrival_time);
        printf("Burst Time for %d process: ",i+1);
        scanf("%d",&p_arr[i].burst_time);
        p_arr[i].remaining_time=p_arr[i].burst_time;
    }
    int clock=0;
    int largest_bt=0,largest_p;
    for(i=0;i<n;i++){
        if(largest_bt<p_arr[i].burst_time){
            largest_bt=p_arr[i].burst_time;
            largest_p=i;
        }
    }
    for(i=0;i<n;i++){
        int short_t=largest_bt,short_p=largest_p;
        for(j=0;j<n;j++){
            if(p_arr[j].remaining_time==0||p_arr[j].arrival_time>clock){
                continue;
            }
            if(p_arr[j].burst_time<short_t){
                short_t=p_arr[j].burst_time;
                short_p=j;
            }
        }
        printf("->%d ",short_p+1);
        p_arr[short_p].remaining_time=0;
        clock+=p_arr[short_p].burst_time;
    }
}