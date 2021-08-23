/************************************************************************
   双调巡游
   File Name: bitonic_traveling_salesman.cpp
   Author: ljl
   Mail: 
   Created Time: 2021年05月22日 15:15:51
************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
#include<tuple>
#include<cmath>
using namespace std;
#define random(x) (rand()%(x+1))

int MAX = 1<<30;
float getDistance(tuple<float, float> p1, tuple<float, float> p2){
	float deltaX = get<0>(p1) - get<0>(p2);
	float deltaY = get<1>(p1) - get<1>(p2);
	
	// cout<<deltaX<<' '<<deltaY<<endl;
	return sqrt(deltaY*deltaY + deltaX*deltaX);
}

int main(){
	vector<tuple<float, float>> vertex {
		{1, 0}, {2, 8}, {3, -8}, {4,9}, 
		{5,-9}, {6, 10}, {7, -10}, {8, 11}};

	sort(vertex.begin(), vertex.end(), [](tuple<float, float> p1, tuple<float, float> p2)->bool{return get<0>(p1) < get<0>(p2);});
	float *distances = new float[vertex.size()*vertex.size()];
	
	//path代表了从i到最左侧节点，再到最右侧节点j的最优解,故j=size, 或i=size 的最小值为最优解
	//注意对于任意i,j path[i][j] 和path[j][i]是等价的，所以只求i>j的情况
	float *path = new float[vertex.size()*vertex.size()];
	//prePosition 代表了path[i][j]，i所连接的前一个节点位置
	int *prePosition = new int[vertex.size()*vertex.size()];
	
	for(int i = 0; i < vertex.size(); i++) {
		for(int j = 0; j < vertex.size(); j++){
			*(distances + i * vertex.size() + j) = getDistance(vertex[i], vertex[j]);
		}
	}
	
	for(int i = 0; i < vertex.size(); i++)
	{
		for(int j = 0; j< vertex.size(); j++){
			cout<<*(distances + i *vertex.size() + j)<<' ';
		}
		cout<<endl;
	}
	cout<<endl;

	*(path + 0 * vertex.size() + 0) = 0;
	*(path + 1 * vertex.size() + 0) = *(distances + 1*vertex.size() + 0);
	*(prePosition + + 1*vertex.size() + 0) = 0;
	
	for(int i = 2; i < vertex.size(); i++){
		for(int j = 0; j < i; j++){
			if(i - 1 > j){
				//此时i-1最右，i只能连接i-1
				*(path + i*vertex.size() + j) = *(path + (i-1)*vertex.size() + j) + *(distances + i*vertex.size() + i - 1);
				*(prePosition + i*vertex.size() + j) = i-1;
				// cout<<i<<' '<<j<<' '<< *(path + i*vertex.size() + j)<<endl;
				// cout<<"dis "<<i<<' '<<i - 1<<' '<< *(distances + i*vertex.size() + i - 1)<<endl;
			}else{
				//此时i-1==j,  i可以连接任意一个小于j的节点
				float min = MAX;
				int pos = -1;
				float t;
				//cout<<"-------"<<endl<<i<<' '<<j<<endl;
				for(int k = 0; k < j; k++){
					cout<<k<<' '<<*(path + j*vertex.size() + k)<<' '<<*(distances + i*vertex.size() + k)<<endl;
					t = *(path + j*vertex.size() + k) + *(distances + i*vertex.size() + k);
					if(t < min){
						min = t;
						pos = k;
						// cout<<"k:"<<k<<' '<<min<<endl;
					}
				}
				// cout<<i<<' '<<j<<' '<< min<<" x"<<endl;
				*(path + i*vertex.size() + j) = min;
				*(prePosition + i*vertex.size() + j) = pos;
			}
		}
	}
	
	//这里i = 0, j = 0是不会输出的，第一个输出的是1,0
	for(int i = 0; i < vertex.size(); i++){
		for(int j = 0; j < i; j++){
			cout<< *(path + i*vertex.size() + j)<<' ';
		}
		cout<<endl;
	}
	
	for(int i = 0; i < vertex.size(); i++){
		for(int j = 0; j < i; j++){
			cout<< *(prePosition + i*vertex.size() + j)<<' ';
		}
		cout<<endl;
	}
	
	float min = MAX;
	int pos;
	
	
	
	vector<int> *left, *right, *t;
	
	//left，right分别保存了两条路径
	left = new vector<int>();
	right = new vector<int>();
	left->push_back(vertex.size() - 1);
	
	
	//注意要求是所有点都到，不是要回到初始节点，所以只有有一个维度是size就可以了
	for(int i = 0 ; i < vertex.size(); i++){
		if(*(path + (vertex.size()-1)*vertex.size() + i) < min){
			min = *(path + (vertex.size()-1)*vertex.size() + i);
			pos = i;
		}
	}
	
	right->push_back(pos);
	left->push_back(*(prePosition + (vertex.size()-1)*vertex.size() + pos));
	
	while(left->size() + right->size() < vertex.size()){
		//因为path只记录的i>j的情况，所以当left的当前（最后）元素小于 right的当前（最后）元素时
		//将left，right交换，求另一侧的路径
		if(left->at(left->size() - 1) < right->at(right->size() - 1)){
				t = left;
				left = right;
				right = t;
		}
		
		pos = *(prePosition + left->at(left->size() - 1)*vertex.size() + right->at(right->size() - 1));
		left->push_back(pos);
	}
	
	
	cout<<"最优值:"<<min<<endl;
	cout<<"路径:";
	for(auto p:*left) cout<<get<0>(vertex[p])<<','<<get<1>(vertex[p])<<" -> ";
	cout<<endl; 
	for(auto p:*right) cout<<get<0>(vertex[p])<<','<<get<1>(vertex[p])<<" -> ";
	cout<<endl;
	
	delete right;
	delete left;
	// for(int i = 0; i< vertex.size(); i++) cout<<accDistance[i]<<' '<<distances[i+1]<<' '<<get<0>(vertex[i])<<' '<<get<1>(vertex[i])<<endl;
	return 0;
}
