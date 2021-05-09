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
		//注意最大公约数值不变，new_x，new_y是b, a%b得到的解，这里针对当前a,b的参数做调整
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
		for(int i = 0; i < d - 1; i++){
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
	vector<int> binary_b;
	int c = 0;
	int d = 1;
	int t, k;
	
	t = b;
	while(b > 0){
		binary_b.push_back(b&1);
		b >>= 1;
	}
	
	std::reverse(binary_b.begin(), binary_b.end());
	for(int i = binary_b.size() - 1; i >= 0; i--){
		//使用位运算，从大到小，移一位就平方一次，当前位为1就乘一次基数
		//c 为bk...bi的二进制值
		//b 为a^c mod n 的结果
		c *= 2;
		d = (d*d)%n;
		if(binary_b[i] == 1){
			c += 1;
			d = (d*a)%n;
		}
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
	cout<<"ax=b(mod n)求解"<<endl;
	cout<<"输入a,b,n:"<<endl;;
	cin>>a>>b>>n;
	modular_linear_equation_solver(a, b, n);
	
	cout<<"反复平方求 a^b mod n"<<endl;;
	cout<<"输入a,b,n:"<<endl;;
	cin>>a>>b>>n;
	cout<<modular_exponentiation(a, b, n)<<endl;
	
	int q,p,e,t,d;
	q = 277, p = 431;
	n = q*p;
	t = (p-1)*(q-1);
	for(int i = 1; i < t/2; i++){
		if(euclid(i*2 + 1, t) == 1){
			e = i*2 + 1;
			break;
		}
	}
	
	d = modular_exponentiation(t,e,n);
	cout<<" q:"<<q<<" p:"<<p<<" t:"<<t<<" e:"<<e<<" d:"<<d<<endl; 
	cout<<"rsa 测试输入a"<<endl;
	cin>>a;
	cout<<a<<" 加密解密："<<modular_exponentiation(modular_exponentiation(a,e,n), d, n);
	
	cout<<""<<endl;
	return 0;
}
