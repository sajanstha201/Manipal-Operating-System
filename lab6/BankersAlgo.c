#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main(){
	int resource_n,process_n;
	printf("Enter the number of process:");
	scanf("%d",&process_n);
	printf("Enter the number of resources:");
	scanf("%d",&resource_n);
	int arr_alloted[process_n][resource_n],arr_requested[process_n][resource_n];
	int arr_finished[process_n],arr_available[resource_n];
	printf("Enter the process resource alloted array\n");
	int i,j,k;
	for(i=0;i<process_n;i++)
		for(j=0;j<resource_n;j++)
			scanf("%d",&arr_alloted[i][j]);
	printf("Enter the process resource request array\n");
	for(i=0;i<process_n;i++)
		for(j=0;j<resource_n;j++)
			scanf("%d",&arr_requested[i][j]);
	printf("Enter the availability of resources\n");
	for(i=0;i<resource_n;i++)
		scanf("%d",&arr_available[i]);
	for(i=0;i<process_n;i++)
		arr_finished[i]=0;
    int sequence[process_n];
	int finished_n=0;
	for(k=0;k<process_n;k++){
		int p;
		for(i=0;i<process_n;i++){
			if(arr_finished[i])
				continue;
			int c=0;
			for(j=0;j<resource_n;j++){
				if(arr_requested[i][j]<=arr_available[j])
					c++;
				else
					break;
			}
			if(c==resource_n){
				for(j=0;j<resource_n;j++)
					arr_available[j]+=arr_alloted[i][j];
                sequence[finished_n]=i;
				finished_n++;
				arr_finished[i]=1;
				break;
			}
		}
	}
    for(i=0;i<process_n;i++)
        printf("%d -> ",sequence[i]);
	if(finished_n==process_n)
		printf("NO DEADLOCK");
	else
		printf("DEADLOCK");
}