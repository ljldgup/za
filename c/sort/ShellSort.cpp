/************************************************************************
    > File Name: ShellSort.cpp
    > Author: ljl
    > Mail: 
    > Created Time: Sat Nov  2 08:19:39 2019
************************************************************************/

#include<iostream>
#include <cstdlib>
#include <ctime>
/* #include"test.h" */
using namespace std;


int shellSort(int *nums, int length){
	int interval = length/2;
	int i,j,k,t;
	
	//需要4层循环，添加分组间距，启示点两层。
	while(interval > 0){
		for(i = 0; i < interval; i++){
			for(j = i + interval; j < length; j += interval){
				k = j - interval;
				t = *(nums + j);
				while(k >= 0 && *(nums + k) > t ){
					*(nums + k + interval) = *(nums + k);
					k -= interval;
				}
				*(nums + k + interval) = t;
			}
		}
		interval /= 2;
	}
}

/* 
int main(){
	srand((int)time(0));
	int len = 100;
	int *nums = new int[len];
	
	for(int i = 0; i < len; i++) *(nums + i) = rand() % len;
	for(int i = 0; i < len; i++)cout << *(nums + i) << ' ';
	cout<< endl;

	shellSort(nums, len);
	for(int i = 0; i < len; i++)cout << *(nums + i) << ' ';
	cout<< endl;
	
	delete[] nums;
} */
