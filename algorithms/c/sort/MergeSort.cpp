
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"test.h"
#define random(x) (rand()%x)
#define MAX_NUMS 40

//¹é²¢ÅÅĞò merge sort
void randgeMergeSort(int *arrays, int st, int ed, int *temp){
	
	//printf("%d %d\n", st, ed);
	if(st == ed) return;
	if(st == ed - 1) {
		if(*(arrays + st) > *(arrays + ed)){
			int t = *(arrays + st);
			*(arrays + st) = *(arrays + ed);
			*(arrays + ed) = t;
			}
		return;
		}

	int len = ed - st;
	int pt1 = st;
	int pt2 = st + (ed - st)/2 + 1;

	randgeMergeSort(arrays, st, st + (ed - st)/2, temp);
	randgeMergeSort(arrays, st + (ed - st)/2 + 1, ed, temp);

	int t = 0;
	
	//merge 
	while(pt1 < st + (ed - st)/2 + 1 || pt2 < ed + 1){
		if(pt1 == st + (ed - st)/2 + 1) *(temp + t ) = *(arrays + pt2++);
		else if(pt2 == ed + 1) *(temp + t) = *(arrays + pt1++);
		else if( *(arrays + pt1) > *(arrays + pt2)) *(temp + t) = *(arrays + pt2++);
		else *(temp + t) = *(arrays + pt1++);
		t++;
		}

	for(int i = 0; i < ed - st + 1; i++){
		*(arrays + st + i) = *(temp + i);
		}

	}

void mergeSort(int *arrays, int length){
	if(arrays == nullptr) return;
	int* t = (int*)malloc((length) * sizeof(int));
	randgeMergeSort(arrays, 0, length - 1, t);
    free(t);
	}
/* 
int main(){
	srand((int)time(0));
	int len = random(MAX_NUMS) + 10;

	int *num1 = (int*)malloc(sizeof(int) * len);
	
	for(int i = 0; i < len; i++) *(num1 + i) = random((len*10));
	//memcpy in string.h
	
	printf("length %d\n", len);
	printf("origin:\n");
	for(int i = 0; i < len; i++) printf("%d ", *(num1 + i));
	printf("\n\n");
    
	mergeSort(num1, len);

	printf("MergeSort\n");
	for(int i = 0; i < len; i++) printf("%d ", *(num1 + i));
	printf("\n\n");

	free(num1);
} */

