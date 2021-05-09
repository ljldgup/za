/************************************************************************
   File Name: multithread.cpp
   Author: ljl
   Mail: 
   Created Time: 2021年05月 7日 23:50:48
************************************************************************/

#include<iostream>
#include<thread>
#include<ctime>
#include <future>
using namespace std;
#define random(x) (rand()%(x+1))

//效果并不好。。
int mutithread_fib(int n){
	if(n == 1) return 1;
	else if(n == 2) return 1;
	else{
		future<int> f1 = async(mutithread_fib, n-1);
		future<int> f2 = async(mutithread_fib, n-2);
		return f1.get() + f2.get();
	}
}

int fib(int n){
	if(n == 1) return 1;
	else if(n == 2) return 1;
	else return fib(n-1) + fib(n-2);
}

constexpr int const_fib(int n){
	if(n == 1) return 1;
	if(n == 2) return 1;
	return const_fib(n-1) + const_fib(n-2);
}

int main(){
	clock_t start,end;
    double endtime;
	
	start=clock();
	cout<<fib(10)<<endl;
	end=clock();
	endtime = (double)(end-start)/CLOCKS_PER_SEC;	
    cout<<"fib time:"<<endtime<<endl;

	start=clock();
	cout<<const_fib(10)<<endl;
	end=clock();
	endtime = (double)(end-start)/CLOCKS_PER_SEC;		
    cout<<"const_fib time:"<<endtime<<endl;
	
	start=clock();	
	cout<<mutithread_fib(10)<<endl;
	end=clock();
	endtime = (double)(end-start)/CLOCKS_PER_SEC;		
    cout<<"mutithread_fib time:"<<endtime<<endl;
	return 1;
}
