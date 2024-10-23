#include<stdio.h>
#include<math.h>
#include<unistd.h>
int main(){
    int np,nr;
        int i,j,k;
    printf("Enter the number of process: ");
    scanf("%d",&np);
    printf("Enter the number of resources: ");
    scanf("%d",&nr);
    int alloc[np][nr],need[np][nr];
    int avl[nr],fns[np];
    printf("Enter the allocation array: \n");
    for(i=0;i<np;i++)
        for(j=0;j<nr;j++)
            scanf("%d",&alloc[i][j]);
    printf("Enter the needed array: \n");
    for(i=0;i<np;i++)
        for(j=0;j<nr;j++)
            scanf("%d",&need[i][j]);
    printf("Enter the availabe array: \n");
    for(i=0;i<nr;i++)
        scanf("%d",&avl[i]);
    for(i=0;i<np;i++)
        fns[i]=0;
    int fn=0;
    int queue[np];
    for(i=0;i<np;i++){
        for(j=0;j<np;j++){
            if(fns[j]==1)
                continue;
            int c=0;
            for(k=0;k<nr;k++)
                if(need[j][k]<=avl[k])
                    c++;
                else
                    break;
            if(c==nr){
                queue[fn]=j;
                fns[j]=1;
                fn++;
                for(k=0;k<nr;k++){
                    avl[k]+=alloc[j][k];
                }
                break;
            }
        }
    }
    for(i=0;i<fn;i++){
        printf("%d->",queue[i]);
    }
    if(fn==np){
        printf("NO DEADLOCK\n");
    }
    else
        printf("DEADLOCK\n");
}