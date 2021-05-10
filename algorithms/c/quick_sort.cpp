/************************************************************************
    > File Name: quickSort.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年03月27日 22:42:01
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x) (rand()%(x))

void exchange(int *array, int q, int r){
	int t = *(array + q);
	*(array + q) = *(array + r);
	*(array + r) = t;
}

//循环不变性，q ~ i的元素都小于x, i+1 ~ j的元素都大于等于x
int partition(int *array, int q, int r){
	int i, j, x;
	i = q - 1;
	j = q;
	x = *(array + r);
	while(j < r){
		if(*(array + j) < x){
			i += 1;
			exchange(array, i, j);
		}
		j++;
	}
	exchange(array, i + 1, r);
	
	return i + 1;
}

int random_partition(int *array, int q, int r){
	int k = random(r - q + 1) + q;
	exchange(array, k, r);
	return partition(array, q, r);
}

void quick_sort(int *array, int q, int r){
	//printf("%d %d\n", q, r);
	if(q >= r) return;
	else{
		int m = random_partition(array, q, r);
		//int m = (r+q)/2;
		//for(int i = 0; i < 10; i++) printf("%d ", *(array + i)); 
		//printf("\n");
		quick_sort(array, q, m - 1);
		quick_sort(array, m + 1, r);
	}
}

int main(){
	srand((int)time(0));
	int length = 10;
	int *array = (int*)malloc(sizeof(int) * length);
	for(int i = 0; i < length; i++) *(array + i) = random(length * 100);

	for(int i = 0; i < length; i++) printf("%d ", *(array + i)); 
	printf("\n");
	quick_sort(array, 0, length - 1);

	for(int i = 0; i < length; i++) printf("%d ", *(array + i)); 
	printf("\n");
	return 0;
}
