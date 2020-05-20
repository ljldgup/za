/************************************************************************
    > File Name: InsertSort.c
    > Created Time: Wed 30 Oct 2019 11:16:06 PM PDT
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"test.h"
#define random(x) (rand()%x)
#define MAX_NUMS 40

void directInsertSort(int *nums, int length){
	int i,j,t;
	for(i = 1; i < length; i++){
		
		j = i - 1;
		t = *(nums + i);
        
        //优化, 不使用冒泡左移，直接一次性往后移动
		while( j >= 0 && *(nums + j) > t){
			*(nums + j + 1) = *(nums + j);
			j--;
		}
		*(nums + j + 1) = t;
	}
}

void bubbleSort(int *nums, int length){
	int i,j,t,k;
	int flag, pos;

	k = 0;
	for(i = 0;  i < length; i++){
		
		flag = 0;
		pos = 0;

		for(j = length - 1; j > k; j--){ 
			if(*(nums + j) < *(nums + j - 1) ){
				t = *(nums + j);
				*(nums + j) = *(nums + j - 1);
				*(nums + j - 1) = t;
				flag = 1;
				pos = j;
			}
		}

		//优化1,没有冒泡说明已经有序
		if(flag == 0) return;
		
		//优化2，记录最后冒泡的位置，后面的数字已经排序，不需要再操作
		k = pos;
	}
}


void selectSort(int *nums, int length){
    /*
	int i,j,t;

	for(i = 0;  i < length; i++){
		for(j = length - 1; j > i; j--){ 
			if(*(nums + j) < *(nums + i) ){
				t = *(nums + j);
				*(nums + j) = *(nums + i);
				*(nums + i) = t;
			}
		}
	}
    */

    //优化，采用下标记录最值，同时查找最大值和最小值
    
    //最小值下标
	int minpos = 0;
	//最大值下标
	int maxpos = 0;
	int left = 0;
	int right = length - 1;
	int t, j = 0;
	//循环length-1次
	while (left < right)
	{
		maxpos = left;
		minpos = left;
		//确定最大值下标以及最小值下标
		for (j = left; j <= right; j++)
		{
			if (nums[j]>nums[maxpos])
			{
				maxpos = j;
			}
			if (nums[j] < nums[minpos])
			{
				minpos = j;
			}
		}
		//将最大值插到最后
		if (maxpos != right)
		{
			t = nums[maxpos];
			nums[maxpos] = nums[right];
			nums[right] = t;
		}
		//防止minpos在最大值要插入的位置
		if (minpos == right)
		{
			minpos = maxpos;
		}
		//将最小值插到最前面
		if (minpos != left)
		{
			t = nums[minpos];
			nums[minpos] = nums[left];
			nums[left] = t;
		}

		left++;
		right--;
	}
}

/* 
int main(){
	srand((int)time(0));
	int len = random(MAX_NUMS) + 10;

	int *num1 = (int*)malloc(sizeof(int) * len);
	int *num2 = (int*)malloc(sizeof(int) * len);
	int *num3 = (int*)malloc(sizeof(int) * len);
	
	for(int i = 0; i < len; i++) *(num1 + i) = random((len*10));
	//memcpy in string.h
	memcpy(num2, num1, sizeof(int) * len);
	memcpy(num3, num1, sizeof(int) * len);
	
	printf("length %d\n", len);
	printf("origin:\n", len);
	for(int i = 0; i < len; i++) printf("%d ", *(num1 + i));
	printf("\n\n");
	
	directInsertSort(num1, len);
	boubbleSort(num2, len);
	selectsort(num3, len);

	printf("directInsertSort\n");
	for(int i = 0; i < len; i++) printf("%d ", *(num1 + i));
	printf("\n\n");

	printf("bubbleSort\n");
	for(int i = 0; i < len; i++) printf("%d ", *(num2 + i));
	printf("\n\n");
	
	printf("selectSort\n");
	for(int i = 0; i < len; i++) printf("%d ", *(num3 + i));
	printf("\n\n");

	free(num1);
	free(num2);
	free(num3);
}
 */