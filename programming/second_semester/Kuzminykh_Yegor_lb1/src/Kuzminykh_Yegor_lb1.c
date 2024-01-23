#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define N 1000
int comp(const void* s1,const void*s2){
	return *(int*)s1-*(int*)s2;
}



int main(){
	int arr[N];
	for (int i = 0; i < N; i++) {
		scanf("%d",&arr[i]);
	}
	int arr_qsort[N];
	memcpy(arr_qsort,arr,sizeof (arr));
	double time_spend1=0.0;
	clock_t start1 = clock();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if(arr[i]>arr[j]){
				int c=arr[j];
				arr[j]=arr[i];
				arr[i]=c;
			}
		}
	}

	clock_t end1 = clock();
	time_spend1+=(double )(end1-start1)/CLOCKS_PER_SEC;
	double time_spend2=0.0;
	clock_t start2=clock();
	qsort(arr_qsort,N,sizeof(int),comp);
	clock_t end2=clock();
	time_spend2+=(double )(end2-start2)/CLOCKS_PER_SEC;
	for (int i = 0; i < N; i++) {
		printf("%d ",arr_qsort[i]);
	}
	printf("\n%lf\n",time_spend1);
	printf("%lf",time_spend2);
	return 0;

}