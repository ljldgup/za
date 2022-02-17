/************************************************************************
    > File Name: 2-4.reverse_pair.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年10月 8日 20:09:04
************************************************************************/

#include<iostream>
#include<vector>
#include<ctime>
using namespace std;
#define random(x) (rand()%(x+1))

int MAX = 2112314212;

void swap(int *nums, int right, int left){
    int t = *(nums + left);
    *(nums + left) = *(nums + right);
    *(nums + right) = t;
}

void merge(int *nums, int left, int mid, int right){
	//cout<<left<<" "<<mid<<" "<<right<<endl;
    int *numsLeft = new int[mid - left + 1 + 1];
    int *numsRight = new int[right - mid + 1];
    for(int i = left; i <= mid; i++) *(numsLeft + i - left) = *(nums + i);
    *(numsLeft + mid - left + 1) = MAX;
    for(int i = mid + 1; i <= right; i++) *(numsRight + i - mid - 1) = *(nums + i);
    *(numsRight + right - mid) = MAX;
    
    int leftPos, rightPos;
    leftPos = rightPos = 0;
    for(int i = left; i <= right; i++){
        if(*(numsLeft + leftPos) < *(numsRight + rightPos)) {
			*(nums + i) = *(numsLeft + leftPos);
			leftPos++;	
		}
        else {
			*(nums + i) = *(numsRight + rightPos);
			rightPos++;
		}
    }
    
}


int getReversPairWithMergeSort(int *nums, int left, int right){
	if(right - left < 1) return 0;
    if(right - left <= 1){
        if(*(nums + left) > *(nums + right)) {
			swap(nums, left, right);
			return 1;
		}
        return 0;
    }
	
	int mid = (left + right)/2;
    int leftCount = getReversPairWithMergeSort(nums, left, mid);
    int rightCount = getReversPairWithMergeSort(nums, mid + 1, right);
    
    int count = 0;
    int rightPos = mid + 1;
    for(int i = left; i <= mid ; i++){
        //这里右边不用回退，直接从上次的地方开始，因为元素已经排序，左边必然大于右边
		while(rightPos <= right && *(nums + rightPos) < *(nums + i)) rightPos++;
		count += rightPos - mid - 1;
	}
    merge(nums, left, mid, right);
    
	return count + leftCount + rightCount;
}

int getReversPair(int *nums, int left, int right){
	int count = 0;
	
	for(int i = left; i < right; i++){
		for(int j = i + 1; j <= right; j++){
			if(*(nums + i) > *(nums + j)) count++;
		}
	}
	
	return count;
}


int main(){
    
    clock_t start,end;
    double endtime;
    srand((int)time(0));
    
    int length = 20000;
    int *nums = new int[length];

    for(int i = 0; i < length; i++) *(nums + i) = random(length*length);
    // for(int i = 0; i < length; i++) cout<< *(nums + i)<<" ";
    // cout<<endl;
    
    start=clock();		//程序开始计时
    //需要先遍历归并完了就排序了 
    int count2 = getReversPair(nums, 0, length - 1);
    end = clock();
    cout<<"遍历结果 "<<count2<<" 时间"<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    
    start = clock();	
    int count1 = getReversPairWithMergeSort(nums, 0, length - 1);
    end = clock();
    cout<<"归并结果 "<<count1<<" 时间"<<(double)(end-start)/CLOCKS_PER_SEC<<endl;

    
    // for(int i = 0; i < length; i++) cout<< *(nums + i)<<" ";
    // cout<<endl;
    
    delete[] nums;
    
	return 0;
}
