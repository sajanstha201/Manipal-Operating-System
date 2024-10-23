#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct{
    int pid;
    int burst_time;
    int arrival_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int remaning_time;
} PROCESS;
void printProcess(int n,PROCESS process[n]){
    int i,totalTurnaround_time=0,totalWaiting_time=0;
    printf("PID\t BT\t AT\t PR\t WT\t TT\t RT\n");
    for(i=0;i<n;i++){
        printf("%d\t %d\t %d\t %d\t %d\t %d\t %d\n",process[i].pid,process[i].burst_time,process[i].arrival_time,process[i].priority,process[i].waiting_time,process[i].turnaround_time,process[i].remaning_time);
        totalTurnaround_time+=process[i].turnaround_time;
        totalWaiting_time+=process[i].waiting_time;
    }
    printf("Average Turn Around Time: %d\n",totalTurnaround_time/n);
    printf("Average Waiting Time: %d\n\n",totalWaiting_time/n);
}
void PreemptiveSJF(int n,PROCESS process[n]){
    int period=0,i,j,k;
    int completed=0;
    while(completed!=n){
        PROCESS *smallest=(PROCESS*)malloc(sizeof(PROCESS));
        smallest->remaning_time=-1;
        for(i=0;i<n;i++)
            if(process[i].remaning_time>0 && process[i].arrival_time<=period){
                process[i].waiting_time++;
                process[i].turnaround_time++;
                if(smallest->remaning_time==-1 || smallest->remaning_time>process[i].remaning_time){
                    smallest=&process[i];
                }
            }
        period++;
        if(smallest->remaning_time==-1){
            continue;
        }
        smallest->remaning_time--;
        smallest->waiting_time--;
        if(smallest->remaning_time<=0){
            completed++;
        }
    }
    printProcess(n,process);
}
void addWaitingTime(int k,int n,PROCESS process[n],int quantum,int time){
    int i;
    for(i=0;i<n;i++){
        if(process[i].remaning_time>0 &&process[i].arrival_time<=time){
            process[i].waiting_time+=quantum;
            process[i].turnaround_time+=quantum;
        }
    }
    process[k].waiting_time-=quantum;
    process[k].remaning_time-=quantum;
}
void RoundRobin(int n,PROCESS process[n]){
    int quantum;
    printf("Enter the Quantum value: ");
    scanf("%d",&quantum);
    int completed=0;
    int time=0;
    int i=0;
    while(completed!=n){
        if(process[i%n].remaning_time>0 && process[i%n].arrival_time<=time){
            if(process[i%n].remaning_time<quantum){
                addWaitingTime(i%n,n,process,quantum,time);
                time+=quantum;
            }
            else{
                addWaitingTime(i%n,n,process,process[i%n].burst_time,time);
                time+=process[i%n].burst_time;
            }
        }
        if(process[i%n].remaning_time==0){
            completed++;
        }
        i++;
    }
    printProcess(n,process);
}
PROCESS* findHighestPriorityProcess(int n, PROCESS process[n],int clock){
    int i;
    PROCESS *highest=(PROCESS*)malloc(sizeof(PROCESS));
    highest->priority=-1;
    for(i=0;i<n;i++)
        if(process[i].arrival_time<=clock && process[i].remaning_time>0)
            if(highest->priority==-1 || highest->priority<process[i].priority)
            highest=process+i;
    return highest;
}
void NonPreemptivePriority(int n,PROCESS process[n]){
    int completed=0;
    int clock=0;
    while(n!=completed){
        PROCESS *highest=findHighestPriorityProcess(n,process,clock);
        int i;
        for(i=0;i<n;i++){
            if(process[i].arrival_time<=clock && process[i].remaning_time>0){
                process[i].waiting_time+=highest->burst_time;
                process[i].turnaround_time+=highest->burst_time;
            }
            if(highest->pid==process[i].pid)
                process[i].waiting_time-=highest->burst_time;
        }
        if(highest->priority==-1){
            clock++;
            continue;
        }   
        highest->remaning_time=0;
        completed++;
        clock+=highest->burst_time;
    }
    printProcess(n,process);
}
void reset(int n,PROCESS process[n]){
    int i;
    for(i=0;i<n;i++){
        process[i].waiting_time=0;
        process[i].turnaround_time=0;
        process[i].remaning_time=process[i].burst_time;
    }
}
int main(){
    printf("Enter the total number of process: ");
    int n_process,i,j,k;
    scanf("%d",&n_process);
    PROCESS process[n_process];
    for(i=0;i<n_process;i++){
        printf("Enter detail for %d process\n",i+1);
        process[i].pid=i;
        printf("Burst Time: ");
        scanf("%d",&process[i].burst_time);
        printf("Arrival Time: ");
        scanf("%d",&process[i].arrival_time);
        printf("Enter Priority: ");
        scanf("%d",&process[i].priority);
        process[i].waiting_time=0;
        process[i].turnaround_time=0;
        process[i].remaning_time=process[i].burst_time;
    }
    while(1){
        printf("1.preemptive SJF\n2.Round Robin\n3.Non Preemptive Priority\n4.stop\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                reset(n_process,process);
                PreemptiveSJF(n_process,process);
                break;
            case 2:
                reset(n_process,process);
                RoundRobin(n_process,process);
                break;
            case 3:
                reset(n_process,process);
                NonPreemptivePriority(n_process,process);
                break;
            case 4:
                return 0;
        }
    }


}