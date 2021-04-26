/************************************************************************
    > File Name: intervalTree.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月16日 11:19:55
************************************************************************/

#include<iostream>
#include<set>
#include<ctime>
using namespace std;
#define random(x) (rand()%(x+1))

struct interval{
	public:
		int low;
		int high;
		int max;

		interval(int l,int h){
			this->low = l;
			this->high = h;
		}
		bool operator<(const interval &right)const{
			// cout<<"???"<<endl;
			// cout<<this->low<<'<'<<right.low<<' ';
			return this->low < right.low;
		}
};

int main(){
	set<interval> intervalTree;
	int low,high;

	for(int i = 0;i < 10; i++){
		low = random(i*10);
		high = low + random(i);
		intervalTree.insert(interval(low,high));
	}

	for(auto i: intervalTree){
		cout<<':'<<i.low<<'~'<<i.high<<endl;
	}
	// if(interval(11,4) < interval(1,3)){
		// cout<<"true";
	// }
	// else{
		// cout<<"false";
	// }
}
