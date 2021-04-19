/************************************************************************
    > File Name: best_binary_tree.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月18日 23:17:53
************************************************************************/

#include<iostream>
#include<vector>
#include<ctime>
#include<limits>
using namespace std;
#define random(x) (rand()%(x+1))

void optimal_bst(float *p,float *q, int n){
	cout<<p<<' '<<q<<' '<<n<<endl;
	float* e = new float[(n+1)*(n+1)];
	float* w = new float[(n+1)*(n+1)];
	int* pos = new int[(n+1)*(n+1)];
	for(int i = 1; i <= n; i++){
		*(e + i*(n+1) + (i-1)) = *(q + i);
		*(w + i*(n+1) + (i-1)) = *(q + i);
	}
	
	float tExp;
	for(int len = 1; len < n + 1; len++){
		//cout<<"len:"<<len<<endl;
		for(int i = 1; i < n - len + 2; i++){
			int j = i + len - 1;
			//cout<<"i:"<<i<<",j:"<<j<<endl;;
			*(w + i*(n+1) + j) = *(w + i*(n+1) + j - 1) + *(p + j) + *(q + j); 
			float expection = numeric_limits<float>::max();
			for(int r = i; r < i + len; r++){
				//cout<<"r:"<<r<<' ';
				tExp = *(e + i*(n+1) + r - 1) + *(e + (r + 1)*(n+1) + j) + *(w + i*(n+1) + j);
				if(tExp < expection){
					expection = tExp;
					*(pos + i*(n+1) + j) = r;
				}
			}
			*(e + i*(n+1) + j) = expection;
		}
		//cout<<"--------------------------------------------"<<endl;
	}

	for(int i = 0; i < n + 1; i++){
		for(int j = 0; j < n + 1; j++){
			cout<<*(e + i*(n+1) + j)<<'\t';
		}
		cout<<endl;
	}

	for(int i = 0; i < n + 1; i++){
		for(int j = 0; j < n + 1; j++){
			cout<<*(pos + i*(n+1) + j)<<' ';
		}
		cout<<endl;
	}
	cout<<*(e +  1*(n+1) + n)<<endl;
	delete e,w,pos;
}

int main(){
	//srand(time(0));
	int n;
	float sum;
	float *q,*p;
	cin>>n;
	
	p = new float[n];
	q = new float[n + 1];
	sum = 0;

	cout.precision(7);

	for(int i = 0; i < n; i++){
		p[i] = random(n*10)/10.0;
		cout<<p[i]<<' ';
		sum += p[i];
	}
	cout<<endl;

	for(int i = 0; i < n + 1; i++){
		q[i] = random(n*10)/10.0;
		cout<<q[i]<<' ';
		sum += q[i];
	}
	cout<<endl;

	for(int i = 0; i < n; i++){
		p[i] /= sum;
		cout<<p[i]<<' ';
	}
	cout<<endl;

	for(int i = 0; i < n + 1; i++){
		q[i] /= sum;
		cout<<q[i]<<' ';
	}
	cout<<endl;

	optimal_bst(p, q, n);
	delete q;
	delete p;
}
