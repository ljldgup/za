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

//右移
//left 开始值， right结束位置
//输出理论上应该是旋转完成的结果
void rotate_with_recursive(int *nums, int left, int right, int rotate_length){

	
	int length = right - left + 1;
	if(rotate_length == 0 || length < rotate_length) return;

	
	//这里的递归是尾递归，可以改成迭代，其循环不变量为left,right以外的旋转完毕，以内的可以通过一次旋转完成
	//这里使用min(length-rotate_length, rotate_length) 交换头尾，分情况进行递归
	if(length/2 < length){
		swap(nums, left, right, rotate_length);
		rotate_with_recursive(nums, left + rotate_length, right, rotate_length);
	}else if(length/2 == length){
		swap(nums, left, right, rotate_length);
	}else{
		int new_rotate_length = length - rotate_length;
		swap(nums, left, right, new_rotate_length);
		rotate_with_recursive(nums, left, right - new_rotate_length, rotate_length - new_rotate_length);
    }

}

void rotate_with_recursive(int *nums,  int rotate_length, int length){
    cout<<"rotate_with_recursive "<<length<<" "<<rotate_length<<endl;
    rotate_with_recursive(nums, 0, length - 1, rotate_length);
}

int gcd(int a, int b){
    if(a < b) return gcd(b,a);
    if(b==0) return a;
    return gcd(b, a%b);
}

void swap_by_step(int *array, int start, int rotate_length, int length){
    start = start % length;
    int t = *(array + start);
    int previous = start;
    int current = (start - rotate_length + length) % length;
    //循环不变式  previous 是 current 按步长rotate_length的上一步
    while(start != current){
        *(array + previous) = *(array + current);
        previous = current;
        //加左移，减右移,  + length 防止负数的时候出问题
        current = (current - rotate_length + length) % length;
    }
    *(array + previous) = t;
}

void rotate_by_step(int *nums,  int rotate_length, int length){
    cout<<"rotate_by_step "<<length<<" "<<rotate_length<<endl;
    int step = gcd(rotate_length, length);
    for(int i = 0; i < step; i++) swap_by_step(nums, i, rotate_length,length);
}




const int length = 30;
int main(){
	int nums[length];
	for(int i = 0;i< length; i++) nums[i] = i;
	for(int i = 0;i< length; i++) cout<<nums[i]<<" ";
	cout<<endl;

    int rotate_length = random(length);
    
	rotate_with_recursive(nums, rotate_length, length);
	for(int i = 0;i< length; i++) cout<<nums[i]<<" ";
	cout<<endl;
    
    for(int i = 0;i< length; i++) nums[i] = i;
    rotate_by_step(nums, rotate_length, length);
	for(int i = 0;i< length; i++) cout<<nums[i]<<" ";
	cout<<endl;
    
	return 0;
}
