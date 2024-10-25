#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
typedef struct {
    int id,size,hole;
} PROCESS;
typedef struct block{
    int id,size;
    int allocated;
    int process;
    struct block *next;
} HOLE;
void bestFit(HOLE * head, int np, PROCESS p[np]){
    int i;

    for(i=0;i<np;i++){
        HOLE *best_block=head;
        HOLE *temp=head;
        int c=0;
        while(temp!=NULL){
            if(best_block->size<temp->size){
                best_block=temp;
            }
            temp=temp->next;
        }
        temp=head;
        while(temp!=NULL){
            if(temp->allocated==0&&temp->size>=p[i].size){
                c=1;
                if(best_block->size>temp->size){
                    best_block=temp;
                }
            }
            temp=temp->next;
        }
        printf("%d %d\n",best_block->id,p[i].id);
        if(c==1){
            best_block->allocated=1;
            p[i].hole=best_block->id;
            best_block->process=i;
        }

    }
    printf("The holes detail are: \n");
    HOLE *temp=head;
    printf("ID\t SIZE\t ALLOCATED\t Process\n");
    while(temp!=NULL){
        printf("%d\t %d\t%d\t %d\n",temp->id,temp->size,temp->allocated,temp->process);
        temp=temp->next;
    }
    printf("The process detail are: \n");
    printf("ID\tSIZE\tHOLE\n");
    for(i=0;i<np;i++)
        printf("%d\t %d\t%d\n",p[i].id,p[i].size,p[i].hole);
}
int main(){
    int nh,np;
    printf("Enter the total number of holes: ");
    scanf("%d",&nh);
    printf("Enter the total number of proess: ");
    scanf("%d",&np);
    int i,j,k;
    printf("Enter the size of holes: ");
    HOLE *head,*prev;
    for(i=0;i<nh;i++){
        HOLE *current=(HOLE*)malloc(sizeof(HOLE));
        int temp;
        scanf("%d",&temp);
        current->size=temp;
        current->allocated=0;
        current->id=i;
        current->process=-1;
        current->next=NULL;
        if(i==0)
            head=current;
        else
            prev->next=current;
        prev=current;
    }
    PROCESS p[np];
    printf("Enter the detail of process: ");
    for(i=0;i<np;i++){
        scanf("%d",&p[i].size);
        p[i].id=i;
        p[i].hole=-1;
    }
    bestFit(head,np,p);
}