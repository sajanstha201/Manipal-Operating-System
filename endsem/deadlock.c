#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(){
    int np,nr;
    printf("Enter the number of process: ");
    scanf("%d",&np);
    printf("Enter the number of resources: ");
    scanf("%d",&nr);
    int alloc[np][nr],request[np][nr];
    int availabe[nr],finished[np];
    int i,j,k;
    printf("Enter the allocation matrix:\n");
    for(i=0;i<np;i++)
        for(j=0;j<nr;j++)
            scanf("%d",&alloc[i][j]);
    printf("Enter the request matrix:\n");
    for(i=0;i<np;i++)
        for(j=0;j<nr;j++)
            scanf("%d",&request[i][j]);
    printf("Enter the availabe resourec:\n");
    for(i=0;i<nr;i++)
        scanf("%d",&availabe[i]);
    for(i=0;i<np;i++)
        finished[i]=0;
    for(k=0;k<np;k++){
        int c;
        for(i=0;i<np;i++){
            if(finished[i])
                continue;
            int l=0;
            for(j=0;j<nr;j++){
                if(request[i][j]<=availabe[j]){
                    l++;
                }
            }
            if(l==j){
                printf("resoure satisifeid for %d\n",k);
                finished[k]=1;
                printf("availabe: ");
                for(j=0;j<nr;j++){
                    availabe[j]+=alloc[k][j];
                    printf("%d ",availabe[j]);
                }
                printf("\n");
                    
                break;
            }
        }
    }
    for(i=0;i<np;i++){
        if(finished[i]==0){
            printf("DeadLock");
            return 0;
        }
    }
    printf("no deadlock\n");
    return 0;
}