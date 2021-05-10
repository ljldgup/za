/************************************************************************
   File Name: auto_test.cpp
   Author: ljl
   Mail: 
   Created Time: 2021年04月26日 15:23:41
************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define random(x) (rand()%(x+1))

int test(int x){
	return x*x;
}

auto test2(int x){
	return test(x);
}

int main(){
	auto i = 5; // i 被推导为 int
	auto arr = new auto(10); // arr 被推导为 int *
	
	cout<<test2(2)<<endl;
	
	std::vector<int> vec = {1, 2, 3, 4};
	if (auto itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) 
		*itr= 4;
	
	for (auto element : vec) 
		std::cout << element << " "; // read only
	std::cout << std::endl;
	
	for (auto &element : vec) 
		element += 1; // writeabl}
	
	for (auto element : vec)
		std::cout << element << " "; // read only
	std::cout << std::endl;
	return 1;
}
