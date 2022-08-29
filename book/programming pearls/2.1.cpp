/************************************************************************
   File Name: 2.1.cpp
   Author: ljl
   Mail: 
   Created Time: Mon 29 Aug 2022 11:23:02 AM CST

通过递归解决数组旋转问题
************************************************************************/

#include<iostream>
#include<algorithm>
#include<ctime>
using namespace std;
#define random(x) (rand()%(x+1))

void swap(int *nums, int left, int right, int swap_length){
	int temp;
	cout<<"swap "<<left<<" "<<right<<" "<<swap_length<<endl;
	for(int i = 0; i < swap_length; i++){
		temp = *(nums + left + i);
		*(nums + left + i) = *(nums + right - swap_length + i + 1);
		*(nums + right - swap_length + i + 1) = temp;
	}

}

//left 开始值， right结束位置
void rotate(int *nums, int left, int right, int rotate_length){
	cout<<"rotate "<<left<<" "<<right<<" "<<rotate_length<<endl;
	
	int length = right - left + 1;
	if(rotate_length == 0 || length < rotate_length) return;

	
	//这里的递归是尾递归，可以改成迭代，其循环不变量为left,right以外的旋转完毕，以内的可以通过一次旋转完成
	//这里使用min(length-rotate_length, rotate_length) 交换头尾，分情况进行递归
	if(length/2 < length){
		swap(nums, left, right, rotate_length);
		rotate(nums, left + rotate_length, right, rotate_length);
	}else if(length/2 == length){
		swap(nums, left, right, rotate_length);
	}else{
		int new_rotate_length = length - rotate_length;
		swap(nums, left, right, new_rotate_length);
		rotate(nums, left, right - new_rotate_length, rotate_length - new_rotate_length);
	}
}


const int length = 30;
int main(){
	int nums[length];
	for(int i = 0;i< length; i++) nums[i] = i;
	for(int i = 0;i< length; i++) cout<<nums[i]<<" ";
	cout<<endl;

	rotate(nums, 0, length - 1, random(length));

	for(int i = 0;i< length; i++) cout<<nums[i]<<" ";
	cout<<endl;

	return 0;
}
