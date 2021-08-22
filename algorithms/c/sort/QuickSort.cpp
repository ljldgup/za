#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//x这里要加() 不然x是表达式时候会报错。
#define random(x) (rand()%(x))
#define MAX_NUMS 10

void quickSortRange(int *nums, int st, int ed){
	if(st >= ed) return;
	int temp = random(ed - st) + st;
	int t = *(nums + temp);
	*(nums + temp) = *(nums + st);

	int left, right;
	left = st;
	right = ed;
	//循环不变式 st~left-1 的值均小于t， right + 1 ~ ed 的值均大于t
	while(left < right){

		//必须分成左右两轮，没法合并成一个循环
		while(left < right && *(nums + right) >= t) right--;
		//left < right 被满足，右侧条件失败
		if(left < right) {
			*(nums + left) = *(nums + right);
			left++;
		}

		while(left < right && *(nums + left) < t) left++;
		if(left < right){
			*(nums + right) = *(nums + left);
			right--;
		}
	}
	//最终left==right 这里left right都无所谓；
	*(nums + left) = t;

	quickSortRange(nums, st, left - 1);
	quickSortRange(nums, left + 1, ed);


	}

void quickSort(int *nums, int length){
	quickSortRange(nums, 0, length - 1);
	}


/* int main()
{
	srand((int)time(0));
	int len = random(MAX_NUMS) + 10;

	int *num1 = (int*)malloc(sizeof(int) * len);
	
	for(int i = 0; i < len; i++) *(num1 + i) = random((len*10));
	
	printf("length %d\n", len);
	printf("origin:\n");
	for(int i = 0; i < len; i++) printf("%d ", *(num1 + i));
	printf("\n\n");
    
	QuickSort(num1, len);

	printf("quickSort\n");
	for(int i = 0; i < len; i++) printf("%d ", *(num1 + i));
	printf("\n\n");

	free(num1);
	} */
