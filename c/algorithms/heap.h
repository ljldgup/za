

#include<iostream>
using namespace std;

/************************************************************************
    > File Name: priority_queue.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021Äê03ÔÂ22ÈÕ 11:17:49
************************************************************************/
#include"string.h"
#include"stdlib.h"
#include"stdio.h"

#define random(x) (rand()%x)

struct heap{
	int size;
	int *array;
};

bool large_than(int *array, int a, int b);
void print_heap(heap hp);
bool smaller_than(int *array, int a, int b);
void max_heapify(heap hp, int i);
void build_max_heap(heap hp);
void heap_sort(heap hp);


