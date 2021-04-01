/************************************************************************
    > File Name: liner_sort.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年03月29日 17:30:03
************************************************************************/

#include<cstdio>
#include<cstdlib>
#include <algorithm>
#include<ctime>
#include<functional>
#include<vector>
#define random(x) (rand()%(x))


int MAX_SIZE=64;
int DIGITS=3;
int K=10;

void print_array(std::vector<int> array){
	std::for_each(array.begin(), array.end(), [=](int n) ->void{printf("%d ", n);});
	printf("\n");
}

void count_sort(int k, std::vector<int> &array, std::function<int(int)> get_k){
	
	printf("%d \n", 10/10) ;
	//初始化为0
	
	int length = array.size();
	std::vector<int> count(k);
	std::vector<int> sorted_array(length);
	
	for(int i = 0; i < length; i++){
		//printf("%d ", get_k(array[i]));
		count[get_k(array[i])]++;
	}
	
	//printf("\n");
	for(int i = 1; i < k; i++){
		count[i] = count[i] + count[i - 1];
	}
	
	
	for(int i = length - 1; i >= 0; i--){
		sorted_array[--count[get_k(array[i])]] = array[i];
		// count[get_k(array[i])]--;
	}
	
	//print_array(sorted_array);

	for(int i = 0; i < length; i++){
		array[i] = sorted_array[i];
	}
}


void radix_sort(std::vector<int> &array){

	int num = 1;
	for(int i = 0; i < DIGITS; i++){
		auto get_k = [=](int n)->int{return n/num%K;};
		count_sort(K, array, get_k);
		print_array(array);
		num *= K;
	}
}

int main(){
	srand(time(0));
	int length = 20;
	std::vector<int> array(length);
	//int count[MAX_SIZE] = {0};
	//int sorted_array[MAX_SIZE]={0};
	for(int i = 0; i < length; i++){
		array[i] =  random(899) + 100;
	}
	print_array(array);
	radix_sort(array);
	
	// count_sort(11, array, [=](int n)->int{return n%10;});
	// print_array(array);
	
	// count_sort(11, array, [=](int n)->int{return n/10%10;});
	// print_array(array);

	// count_sort(11, array, [=](int n)->int{return n/100;});
	print_array(array);
	return 1;
	
}
