/************************************************************************
    > File Name: priority_queue.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年03月22日 11:17:49
************************************************************************/
#include"string.h"
#include"stdlib.h"
#include"stdio.h"
#include"heap.h"
#define random(x) (rand()%(x))

void exchange(int *array, int a, int b){
	int t = *(array + a - 1);
	*(array + a - 1) = *(array + b - 1);
	*(array + b - 1) = t;
}

bool large_than(int *array, int a, int b){
	return *(array + a - 1) > *(array + b - 1);
}

void print_heap(heap *hp){

	for(int i = 0; i < hp->size; i++){
		printf("%d ", *(hp->array + i));
	}
	printf("\n");
}

bool smaller_than(int *array, int a, int b){
	return *(array + a - 1) < *(array + b - 1);
}

void max_heapify(heap *hp, int i){
	// printf("%d\n", i);
	if( i > hp->size) return;

	int smallest = i;
	int left = 2*i ;
	int right = 2*i + 1;
	if(left <= hp->size && smaller_than(hp->array, smallest, left) ){
		smallest = left;
	}
	if(right <= hp->size && smaller_than(hp->array, smallest, right)){
		smallest = right;
	}
	if(smallest != i){
		exchange(hp->array, i, smallest);
		//子树被交换后已经不满足堆的性质了
		max_heapify(hp, smallest);
	}
}

void build_max_heap(heap *hp){
	for(int i = hp->size/2 + 1; i > 0; i--){
		max_heapify(hp, i);
		//print_heap(hp);
	}
}

void heap_sort(heap *hp){
	build_max_heap(hp);

	int length = hp->size;
	for(int i = 1; i < length; i++ ){
		exchange(hp->array, 1, hp->size);
		hp->size -= 1;
		max_heapify(hp, 1);
	}

	hp->size = length;
}


int extract_first(heap *hp){
	int t = *(hp->array);
	*(hp->array) = *(hp->array + hp->size - 1);
	hp->size -= 1;
	max_heapify(hp, 1);
	return t;
}

//这里应该是替换，将原来i位置，替换为key, key值必须比原来的值大
void heap_insert_key(heap *hp, int i, int key){
	if(hp->size < i || key < *(hp->array + i - 1)){
		return;
	}
	
	*(hp->array + i - 1) = key;
	//第n个节点的子元素 为 2n, 2n+1 故子节点的父节点必然为i/2
	while( i > 1 && *(hp->array + i/2 - 1) < key){
		exchange(hp->array, i/2, i);
		i /= 2;
	}
}

//堆的插入都是吧数据放在数组的最后，然后再调整
void max_heap_insert(heap *hp, int key){
		hp->size += 1;
		*(hp->array + hp->size - 1) = -100;
		heap_insert_key(hp, hp->size, key);
}

int main(){
	int i = 0;
	int size = 0;
	heap hp;
	printf("输入尺寸 ");
	scanf("%d", &size);
	
	hp.size = size;
	hp.array = (int*)malloc(sizeof(int) * size * 10);
	
	for(i = 0; i < size; i++) *(hp.array + i) = random((size*100));
	
	print_heap(&hp);
	heap_sort(&hp);
	print_heap(&hp);
	
	i = 1;
	while(i < size - i + 1){
		exchange(hp.array, i, hp.size - i + 1);
		i++;
	}
	print_heap(&hp);
		
	for(i = 0; i < size; i++){
		printf("%d extract\n", extract_first(&hp));
		print_heap(&hp);


		if(i%2 == 0){
			int t = random(size*500);
			printf("%d insert\n", t);
			max_heap_insert(&hp, t);
			print_heap(&hp);
		}
		
	}
	
	free(hp.array);
	system("pause");
}


