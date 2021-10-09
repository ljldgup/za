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
	int maxPos = mid + 1;
	int maxSumRight = *(array + mid + 1);
	for(i = mid + 2; i <= right; i++){
		sum += *(array + i);
		if(sum > maxSumRight){
			maxSumRight = sum;
			maxPos = i;
		}
	}
	ed = maxPos;
	
	sum = 0;
	maxPos = mid;
	int maxSumLeft = *(array + mid);
	for(i = mid - 1; i >= left; i--){
		sum += *(array + i);	
		if(sum > maxSumLeft){
			maxSumLeft=sum;
			maxPos=i;
		}
	}
	st = maxPos;

	if(leftMax > maxSumRight + maxSumLeft && leftMax > rightMax){
		st = leftSt;
		ed = leftEd;
		return leftMax; 
	}
	else if(rightMax > maxSumRight + maxSumLeft){
		st = rightSt;
		ed = rightEd;
		return rightMax;
	}
    cout<<st<<" "<<ed<<endl;
	return maxSumRight + maxSumLeft;
}

int maxSubArray2(int *array, int left, int right, int &st, int &ed){
    int maxSum = MIN;
    int tmpSum = 0;
    int tmpSt = 0;
    st = ed = left;
    for(int i = left; i < right; i++){
        if( tmpSum + *(array + i) < 0){
            tmpSt = i + 1;
            tmpSum = 0;
            continue;
        }
        
        tmpSum += *(array + i);
        if(tmpSum > maxSum){
            st = tmpSt;
            ed = i;
            maxSum = tmpSum;
        }
    }
    
    return maxSum;
}

int main(){
	int *array = new int[10];
	
	for(int i = 0; i < 10; i++) *(array + i) = random(100) - 50;
	for(int i = 0; i < 10; i++) cout<<*(array + i)<<' ';
	cout<<endl;
	
	int st,ed, maxSum;
	maxSum = maxSubArray(array, 0, 9, st, ed);
	cout<<maxSum<<' '<<st<<' '<<ed<<endl;
    
    maxSubArray2(array, 0, 9, st, ed);
    cout<<maxSum<<' '<<st<<' '<<ed<<endl;
	return 0;
}
