/************************************************************************
   File Name: function_test.cpp
   Author: ljl
   Mail: 
   Created Time: 2021年04月26日 16:02:22
************************************************************************/

#include<iostream>
#include<algorithm>
#include<ctime>
#include<functional>
using namespace std;
#define random(x) (rand()%(x+1))

auto get_student(int id)
{
	// 返回类型被推断为 std::tuple<double, char, std::string>
	if (id == 0)
	return std::make_tuple(3.8, 'A', "张三");
	if (id == 1)
	return std::make_tuple(2.9, 'C', "李四");
	if (id == 2)
	return std::make_tuple(1.7, 'D', "王五");
	return std::make_tuple(0.0, 'D', "null");
	// 如果只写 0 会出现推断错误, 编译失败
}
int foo(int a, int b, int c) {
	return a+b+c;
}

int main(){
	auto add = [](auto x, auto y) {
		return x+y;
	};
	cout<<add(1, 2)<<endl;
	cout<<add(1.1, 2.2)<<endl;
	
	//科里化,使用 std::placeholders::_1 来对第一个参数进行占
	auto bindFoo = std::bind(foo, std::placeholders::_1, 1,2);
	cout<<bindFoo(1)<<endl;
	
	auto student = get_student(0);
	std::cout << "ID: 0, ";
	std::cout << "GPA: " << std::get<0>(student) << ", ";
	std::cout << "成绩: " << std::get<1>(student) << ", ";
	std::cout << "姓名: " << std::get<2>(student) << '\n';
	
	double gpa;
	char grade;
	std::string name;
	// 元组进行拆包
	std::tie(gpa, grade, name) = get_student(1);
	std::cout << "ID: 1, ";
	std::cout << "GPA: " << gpa << ", ";
	std::cout << "成绩: " << grade << ", ";
	std::cout << "姓名: " << name << '\n';
	
	return 1;
}
