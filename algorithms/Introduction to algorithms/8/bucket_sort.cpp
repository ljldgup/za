/************************************************************************
    > File Name: bucket_sort.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月 1日  9:00:06
************************************************************************/

#include<iostream>
#include<vector>
#include<ctime>
#include<functional>
#include<algorithm>
using namespace std;
#define random(x) (rand()%(x))

int MAX_NUMBER=100000;
int BUCKET_NUM=10;


void bucket_insert(vector<int> &bucket, int num){
	bool inserted = false;
	for (auto it = bucket.begin(); it != bucket.end(); ++it){
		if(*it > num){
			inserted = true;
			bucket.insert(it, num);
			break;
		}
	}
	
	if(!inserted){
		bucket.push_back(num);
	}
}

void bucket_sort(vector<int> &nums, int n, function<int(int)> get_bucket_num){
    vector<vector<int>> buckets;
	for(int i = 0; i < n; i++){
		vector<int> bucket;
		buckets.push_back(bucket);
	}
	
	int bucket_num;
	for(auto num: nums){
		bucket_num = get_bucket_num(num);
		bucket_insert(buckets[bucket_num], num);
	}
	
	for(int i = 0; i < nums.size(); i++){
		for(auto bucket: buckets){
			for(auto num:bucket){
				nums[i++] = num;
			}
		}
	}
}


int main(){
	int length = random(BUCKET_NUM*10);
	vector<int> nums(length);
	//for(int i = 0; i < length; i++) nums[i] = random(MAX_NUMBER);
	for_each(nums.begin(), nums.end(), [=](int &n)->void{n = random(MAX_NUMBER);});
	auto get_bucket_num = [=](int n) -> int{return n * BUCKET_NUM / MAX_NUMBER;};
	bucket_sort(nums, BUCKET_NUM, get_bucket_num);
	for(auto i:nums){
		cout<<i<<" ";
	}
}
