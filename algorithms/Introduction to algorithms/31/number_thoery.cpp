/************************************************************************
   File Name: number_thoery.cpp
   Author: ljl
   Mail: 
   Created Time: 2021年05月 9日  0:57:34
************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define random(x) (rand()%(x+1))
int MAX = 999999;

//推论31.22的测试,a*i%b 随着i的增加等分布在0-b之间，按0-b周期分布,
void distributeTest(){
	cout<<"a*i%b 周期分布测试"<<endl;
	int a = random(50);
	int b = random(100) + 30;
	int st = random(100);
	cout<<"a:"<<a<<" b:"<<b<<endl;
	
	vector<int> rst;
	//for(int i = 0; i < b + 1; i++){
	for(int i = st; i < st + b; i++){
		rst.push_back(i*a%b);
	}
	sort(rst.begin(), rst.end(), [](int x, int y)->bool{return x>y;});
	for_each(rst.begin(), rst.end(), [](int x)->void{cout<<x<<' ';});
	cout<<endl;
}

//最大公约数
int gcb(int a, int b){
	if(a < b){
		int t = a;
		a = b;
		b = t;
	}

	if(a % b == 0) return b;
	else return gcb(b, a%b);
}

//最大公约数欧几里得算法
int euclid(int a, int b){
	if(b == 0) return a;
	//该表达式保证后续递归调用过程， b < a
	else return euclid(b, a%b);
}

int extended_euclid(int a, int b, int &x, int &y){
	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	else{
		int new_x, new_y, result;
		result = extended_euclid(b, a%b, new_x, new_y);
		// 注意最大公约数值不变，new_x，new_y是b, a%b得到的解，这里针对当前a,b的参数做调整
		//（new_x*b + new_y*(a%b) = xa + yb）
		x = new_y;
		y = -a/b*new_y + new_x;
		return result;
 	}
}

//模线性方程求解
int modular_linear_equation_solver(int a, int b, int n){
	int x0, x, y, d, t;
	d = extended_euclid(a, n, x, y);
	cout<<a<<' '<<n<<"最大公约数"<<d<<endl;
	cout<<a<<' '<<n<<"最大公约数ax+by表达"<<" = "<<x<<"*"<<a<<" + "<<y<<"*"<<n<<endl;
	
	if(b%d == 0){
		x0 = (x*(b/d))%n; 
		cout<<"x0:"<<x0<<endl;
		for(int i = 0; i < d; i++){
			t = (x0 + i*(n/d))%n;
			cout<<"解"<<i<<":"<<t<<" "<<a*t<<"="<<(a*t - b)/n<<"*"<<n<<"+"<<b<<endl;
		}
		return x0;
	}else{
		cout<<b<<" "<<d<<"无解"<<endl;
		return MAX;
	}
}

int modular_exponentiation(int a, int b, int n){
	// cout<<a<<' '<<b<<' '<<n<<endl;
	vector<int> binary_b;
	int c = 0;
	int d = 1;
	int t, k;
	
	t = b;
	while(b > 0){
		binary_b.push_back(b&1);
		b >>= 1;
	}
	
	//std::reverse(binary_b.begin(), binary_b.end());
	for(int i = binary_b.size() - 1; i >= 0; i--){
		//使用位运算，从大到小，移一位就平方一次，当前位为1就乘一次基数
		//c 为bk...bi的二进制值
		//   b 为a^c mod n 的结果
		c *= 2;
		d = (d*d)%n;
		if(binary_b[i] == 1){
			c += 1;
			d = (d*a)%n;
		}
		// cout<<c<<endl;
		// cout<<d<<endl;
	}
	return d;
}

int main(){
	int a,b;
	// cout<<"a,b最大公约数求解求解"<<endl;
	// cout<<"输入a,b"<<endl;;
	// cin>>a>>b;
	// cout<<a<<' '<<b<<"最大公约数"<<endl<<gcb(a, b)<<endl;
	// cout<<a<<' '<<b<<"最大公约数"<<euclid(a, b)<<endl;
	
	// int x, y;
	// cout<<a<<' '<<b<<"最大公约数"<<extended_euclid(a, b, x, y)<<endl;
	// cout<<a<<' '<<b<<"最大公约数ax+by表达"<<" = "<<x<<"*"<<a<<" + "<<y<<"*"<<b<<endl;
	

	int n;
	// cout<<"ax=b(mod n)求解"<<endl;
	// cout<<"输入a,b,n:"<<endl;;
	// cin>>a>>b>>n;
	// modular_linear_equation_solver(a, b, n);
	
	// cout<<"反复平方求 a^b mod n"<<endl;;
	// cout<<"输入a,b,n:"<<endl;;
	// cin>>a>>b>>n;
	// cout<<modular_exponentiation(a, b, n)<<endl;
	
	distributeTest();
	
	cout<<"rsa测试 a^b mod n"<<endl;;
	int q,p,e,t,d;
	q = 7 , p = 11;
	n = q*p;
	t = (p-1)*(q-1);
	d = -1;
	for(int i = 1; i < t/2; i++){
		if(euclid(i*2 + 1, t) == 1){
			e = i*2 + 1;
			d = modular_linear_equation_solver(e, 1, t);
			if(d > 0 && d != MAX) break;
		}
	}
	
	//如果加密字节，输出的范围有些大于字节范围，需要根据用多个字节存储
	cout<<" q:"<<q<<" p:"<<p<<" n:"<<n<<" t:"<<t<<" e:"<<e<<" d:"<<d<<endl; 
	cout<<e*d<<endl;
	//这里由于是mod n 所以输入要小于n
	cout<<"rsa 测试输入a(小于"<<n<<")"<<endl;
	cin>>a;
	int enc = modular_exponentiation(a,e,n);
	cout<<a<<" 加密："<<enc<<endl; 
	cout<<a<<" 解密："<<modular_exponentiation(enc, d, n)<<endl; 
	cout<<a<<" 加密解密："<<modular_exponentiation(a, e*d, n)<<endl; 
	
	cout<<""<<endl;
	return 0;
}
