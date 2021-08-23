/************************************************************************
   File Name: max_sub_array.cpp
   Author: ljl
   Mail: 
   Created Time: 2021年05月14日 16:43:21
************************************************************************/

#include<iostream>
#include<algorithm>
#include<ctime>
using namespace std;
#define random(x) (rand()%(x+1))
int MIN = -1<<31;

int maxSubArray(int *array, int left, int right, int &st, int &ed){
	//cout<<left<<' '<<right<<endl;
	if(left >= right){
		st = ed = left;
		return MIN;
	}

	int mid = (right + left)/2;
	int leftSt,leftEd, rightSt, rightEd;

	int leftMax = maxSubArray(array, left, mid, leftSt, leftEd);
	int rightMax = maxSubArray(array, mid+1, right, rightSt, rightEd);

	int i;
	
	int sum = 0;
	int maxPos = mid;
	int maxSum = 0;
	for(i = mid + 1; i <= right; i++){
		sum += *(array + i);
		if(sum > maxSum){
			maxSum = sum;
			maxPos = i;
		}
	}
	ed = maxPos;
	
	sum = 0;
	maxPos = mid;
	maxSum = 0;
	for(i = mid - 1; i >= left; i--){
		sum += *(array + i);	
		if(sum > maxSum){
			maxSum=sum;
			maxPos=i;
		}
	}
	st = maxPos;


	if(leftMax > maxSum && leftMax > leftMax){
		st = leftSt;
		ed = leftEd;
		return leftMax; 
	}
	else if(rightMax > maxSum){
		st = rightSt;
		ed = rightEd;
		return rightMax;
	}
	return maxSum;
}

int main(){
	int *array = new int[10];
	
	for(int i = 0; i < 10; i++) *(array + i) = random(10) - 5;
	for(int i = 0; i < 10; i++) cout<<*(array + i)<<' ';
	cout<<endl;
	
	int st,ed, maxSum;
	maxSum = maxSubArray(array, 0, 9, st, ed);
	cout<<maxSum<<' '<<st<<' '<<ed;
	return 0;
}
