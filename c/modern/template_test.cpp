/************************************************************************
    > File Name: template_test.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月26日 14:32:02
************************************************************************/


#include <iostream>

template<typename T, typename U>
auto add3(T x, U y){
	return x + y;
}

template<typename ... T>
auto sum(T ... t) {
	return (t + ...);
}
 
int main() {
	std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
	std::cout << add3(1, 2.1) << std::endl;
}
