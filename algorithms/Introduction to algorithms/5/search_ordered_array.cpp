/************************************************************************
   File Name: search_ordered_array.cpp
   Author: ljl
   Mail: 
   Created Time: Mon Aug 23 00:55:47 2021
************************************************************************/

#include<iostream>
#include<algorithm>
#include<ctime>
using namespace std;
#define random(x) (rand()%(x+1))



int random_select(int *nums, int target, int length){
	cout<<"target="<<target<<endl;
	cout<<"length="<<length<<endl;
	bool *used = new bool[length]();
	int usedCount = 0;
	int count = 0;
	int index;

	while(usedCount < length){
		index = random(length - 1);
		if(!used[index]){
			used[index] = true;
			if(*(nums + index) == target) {
				cout<<"count="<<count<<endl;
				return index;
			}
			usedCount++;
		}
		count++;
	}
	delete used;

	//搜索的次数应该是 1 + n/(n-1) .... = n(1/2 + 1/(n-1) + /1(n-2) + ....) < n*logn
	cout<<"count="<<count<<endl;
	return -1;
}

int main(){
	srand(time(0));
	int length = random(100) + 100;
	int *nums = new int[length];
	for(int i = 0; i < length; i++) *(nums + i) = random(length * length);
	
	for(int i = 0; i < length; i++) cout<<*(nums + i)<<" ";
	cout<<endl;

	int targetIndex = random(length);
	cout<<random_select(nums, *(nums + targetIndex), length)<<endl;
	delete nums;
	return 0;
}
