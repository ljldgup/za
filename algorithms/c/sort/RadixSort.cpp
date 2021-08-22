
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cstring>
//<cxx> == "xx.h" in c
#include"test.h"

#define random(x) (rand()%(x))
#define MAX_NUMS 10


int getNumInPos(int num,int pos)
{
    for (int i = 0; i < pos; i++) num /= 10;

    return num%10;
}

int getDigits(int num) 
{
    int count = 0;
    while(num > 0 ){
        num /= 10;
        count++;
    }
    return count;
}

void radixSortN(int *nums, int length, int n, int *digitCount)
{
	int i,j,k;
    int record[10] = {0};
    for(i = 0; i < length; i++) {
        k = getNumInPos(*(nums + i), n);
		*(digitCount + k * length + record[k]) = *(nums + i);
        record[k]++;
	}
    
    k = 0;
    for(i = 0; i < 10; i++){ 
        for(j = 0; j < record[i]; j++) *(nums + k++) = *(digitCount + i * length + j);
    }
}


void radixSort(int *nums, int length)
{
    int max;
    int i;
    max = *nums;
    for(i = 0; i < length; i++) {
        if( *(nums + i) > max) max = *(nums + i);
    }
    
    int digits = getDigits(max);
    int *digitCount = (int*)malloc(sizeof(int) * length * 10);
    for(i = 0; i < digits; i++){
        radixSortN(nums, length, i, digitCount);
    }
}




//采用数组索引排序，也是一种特殊的桶排序方法,分布不密集时会有大量浪费
void countSort(int *nums, int length) {
    int max, min;
    int i,j,k;
    max = min = *nums;
    for(i = 0; i < length; i++) {
        if( *(nums + i) > max) max = *(nums + i);
        else if (*(nums + i) < min) min = *(nums + i);
    }
    
    int numRange = max-min+1;
    int* counter = (int*)malloc(sizeof(int) * numRange);
    memset(counter, 0, sizeof(int)*numRange);
    for(i = 0; i < length; i++) counter[*(nums + i) - min]++;
    k = 0;
    for(i = 0; i < numRange; i++) {
        for(j = 0; j < counter[i]; j++) {
            *(nums + k++) = i + min;
        }
    }
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
    
	radixSort(num1, len);

	printf("countSort\n");
	for(int i = 0; i < len; i++) printf("%d ", *(num1 + i));
	printf("\n\n");

	free(num1);
	}
 */