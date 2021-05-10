/************************************************************************
    > File Name: constexpr_test.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月26日 14:41:05
************************************************************************/

#include<iostream>
#include<algorithm>
#include<ctime>
using namespace std;
#define random(x) (rand()%(x+1))

constexpr int fibonacci(const int n) {
	if(n == 1) return 1;
	if(n == 2) return 1;
	return fibonacci(n-1) + fibonacci(n-2);
}

int main(){
	//实际上编译的时候把表达式替换成常量表达式, 如 fib(3) = fib(2) + f(1) = 1 + 1;
	double test[fibonacci(5)];
	cout<<fibonacci(10)<<endl;
	int i;
	cin>>i;
	cout<<fibonacci(i);
	
	// for( i = 0; i < 3; i++){
		// //这里传入变量会报错？？
		// cout<<fibonacci(i)<<" ";
	// }
	
	return 1;
}
