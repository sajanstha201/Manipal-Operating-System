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
        holes[i].availabe_size=holes[i].total_size;
    }
    printf("Enter the total number of process: ");
    scanf("%d",&np);
    PROCESS processses[np];
    printf("Enter the size of each process: ");
    for(i=0;i<np;i++){
        processses[i].id=i;
        scanf("%d",&processses[i].total_size);
        processses[i].hole=-1;
    }
    for(i=0;i<np;i++){
        for(j=0;j<nh;j++){
            if(processses[i].total_size<=holes[j].availabe_size ){
                holes[j].availabe_size=holes[j].availabe_size-holes[i].total_size;
                processses[i].hole=holes[j].id;
                break;
            }
        }
    }
    printf("The holes status:\n");
    printf("ID\tTotal Size\tAvaliable size\n");
    for(i=0;i<nh;i++){
        printf("%d\t %d\t\t %d\n",holes[i].id,holes[i].total_size,holes[i].availabe_size);
    }
    printf("\n The process status:\n");
    printf("ID\tTotal Size\t Holes\n");
    for(i=0;i<np;i++){
        printf("%d\t %d\t\t %d\n",processses[i].id,processses[i].total_size,processses[i].hole);
    }

}