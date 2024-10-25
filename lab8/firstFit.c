#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct {
    int id;
    int total_size;
    int availabe_size;
} HOLE;
typedef struct {
    int id;
    int total_size;
    int hole;
} PROCESS;
void printHP(int nh,HOLE holes[nh],int np,PROCESS processes[np]){
    int i;
    printf("The holes status:\n");
    printf("ID\tTotal Size\tAvaliable size\n");
    for(i=0;i<nh;i++){
        printf("%d\t %d\t\t %d\n",holes[i].id,holes[i].total_size,holes[i].availabe_size);
    }
    printf("\n The process status:\n");
    printf("ID\tTotal Size\t Holes\n");
    for(i=0;i<np;i++){
        printf("%d\t %d\t\t %d\n",processes[i].id,processes[i].total_size,processes[i].hole);
    }
}
void initializeHP(int nh,HOLE holes[nh],int np, PROCESS processes[np]){
    int i;
    for(i=0;i<np;i++)
        processes[i].hole=-1;
    for(i=0;i<nh;i++)
        holes[i].availabe_size=holes[i].total_size;
}
void firstFit(int nh,HOLE holes[nh],int np, PROCESS processes[np]){
    int i,j;
    for(i=0;i<np;i++){
        for(j=0;j<nh;j++){
            if(processes[i].total_size<=holes[j].availabe_size ){
                holes[j].availabe_size=holes[j].availabe_size-processes[i].total_size;
                processes[i].hole=holes[j].id;
                break;
            }
        }
    }
        printf("This is the result from first fit\n");
    printHP(nh,holes,np,processes);
}
void sortHoles(int nh,HOLE holes[nh]){
    int i,j;
    for(i=0;i<nh;i++){
        for(j=0;j<nh-i-1;j++){
            if(holes[j].availabe_size>holes[j+1].availabe_size){
                HOLE temp;
                temp=holes[j];
                holes[j]=holes[j+1];
                holes[j+1]=temp;
            }
        }
    }
}
void bestFit(int nh,HOLE holes[nh],int np, PROCESS processes[np]){
    int i,j;
    for(i=0;i<np;i++){
        sortHoles(nh,holes);
        for(j=0;j<nh;j++){
            if(processes[i].total_size<=holes[j].availabe_size){
                processes[i].hole=holes[j].id;
                holes[j].availabe_size=holes[j].availabe_size-processes[i].total_size;
                break;
            }
        }
    }
    printf("This is the result from best fit:\n");
    printHP(nh,holes,np,processes);
}
int main(){
    int nh,np;
    printf("Enter the total number of hole: ");
    scanf("%d",&nh);
    HOLE holes[nh];
    int i,j,k;
    printf("Enter the size of each holes: ");
    for(i=0;i<nh;i++){
        holes[i].id=i;
        scanf("%d",&holes[i].total_size);
    }
    printf("Enter the total number of process: ");
    scanf("%d",&np);
    PROCESS processses[np];
    printf("Enter the size of each process: ");
    for(i=0;i<np;i++){
        processses[i].id=i;
        scanf("%d",&processses[i].total_size);
    }
    initializeHP(nh,holes,np,processses);
    firstFit(nh,holes,np,processses);
    initializeHP(nh,holes,np,processses);
    bestFit(nh,holes,np,processses);
}