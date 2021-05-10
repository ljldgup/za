/************************************************************************
   File Name: parallel.cpp
   Author: ljl
   Mail: 
   Created Time: 2021年05月 8日 10:22:58
************************************************************************/

#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
#define random(x) (rand()%(x+1))

int v = 1;

void critical_section(int change_v) {
	static std::mutex mtx;
	mtx.lock();

	// 执行竞争操作
	v = change_v;
	// 离开此作用域后 mtx 会被释放
	mtx.unlock();
}

int main(){
	std::thread t([](){
		std::cout << "hello world." << std::endl;
	});
	t.join();
	
	std::thread t2(critical_section, 2), t3(critical_section, 3);
	t2.join();
	t3.join();
	std::cout << v << std::endl;
	return 1;
}
