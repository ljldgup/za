/************************************************************************
   File Name: KDTree.cpp
   Author: ljl
   Mail: 
   Created Time: Sat Sep 25 00:18:08 2021
************************************************************************/

#include<iostream>
#include<algorithm>
#include<ctime>
#include<cmath>
using namespace std;
#define random(x) (rand()%(x+1))

const int MAX = 10000000;
const int MIN = -10000000;

double getDistance(int *p1, int *p2, int dimensionNum){
	double distance = 0;
	for(int i = 0; i < dimensionNum; i++){
		distance += (*(p1 + i) - *(p2 + i))*(*(p1 + i) - *(p2 + i));
	}
	
	return sqrt(distance);
}


		
class KDNode{
	public:
		int dimension;
		int median;
		int *data;
		int dimensionNum;
		//每个维度的界限 
		int *limit;
		
		KDNode *left;
		KDNode *right;
		KDNode(int dimensionNum, int dimension, int median, int *data){
			this->dimension = dimension;
			this->median = median;
			//被作为节点的是中位数，应该不会在改动
			this->data = data;
			this->dimensionNum = dimensionNum;
			//data内容在partition中会被替换
			//data = new int[dimensionNum];
			//memcpy(this->data,data, sizeof(int) * dimensionNum);
			left = nullptr;
			right = nullptr;
			limit = new int[dimensionNum * 2];
		}
		
		int getLowerLimit(){
			return *(limit + 2*dimension);
		}
		
		int getUpperLimit(){
			return *(limit + 2*dimension + 1);
		}
				
		void print(){
			//cout<<"dimension "<<dimension<<", median "<<median<<endl;
			for(int i = 0; i < dimensionNum; i++){
				cout<<*(data + i)<<" "; 
			}
			cout<<endl;
		}
		
		~KDNode(){
			if(left != nullptr) delete left;
			if(right != nullptr) delete right;
		}
};

class KNearest{
	public:
		int *point;
		int *points;
		double *distances;
		int dimensionNum;
		int count;
		int k;

		KNearest(int *point, int dimensionNum, int k){
			this->point = point;
			this->dimensionNum = dimensionNum;
			this->k = k;
			
			this->points = new int[k*dimensionNum];
			this->distances = new double[k];
			
			count = 0;
		}
		
		
		bool tryInsertPoint(int  *data){
			double distance = getDistance(data, point, dimensionNum);
			if(count < k || distance < distances[count - 1]){
				int insertPos = count > 0 ? count : 0;
				while(insertPos > 0 && distance < distances[insertPos - 1]) insertPos--;
				
				int copyPos = count == k ? count  - 1: count;
				while(copyPos > insertPos) {
					memcpy(points + copyPos*dimensionNum, points + (copyPos - 1)*dimensionNum, sizeof(int)*dimensionNum);
					*(distances + copyPos) = *(distances + copyPos - 1);
					copyPos--;
				}
				
				memcpy(points + insertPos*dimensionNum, data, sizeof(int)*dimensionNum);
				*(distances + insertPos) = distance;
				
				
				if(count < k) count++;
				return false;
			}
			
			return false;
		}
		
		bool intersectWith(KDNode *node){
			double diameter = getDistance(point, points + (k - 1) * dimensionNum, dimensionNum);
			double left = *(point + node->dimension) - diameter;
			double right = *(points + node->dimension) + diameter;
			
			int lowerLimit = node->getLowerLimit();
			int upperLimit = node->getUpperLimit();
			//cout<<"intersectWith"<<endl;
			//cout<<diameter<<" "<<left<<" "<<right<<endl;
			//cout<<node->median<<" "<<lowerLimit<<" "<<upperLimit<<endl;

			if(left > upperLimit || right < lowerLimit){
				//cout<<"not intersected"<<endl;
				return false; 
			} 
			
			//cout<<"intersected"<<endl;
			return true;
		}
		
		bool smallerThanMedian(KDNode *node){
			return *(points + node->dimension) < node->median;
		}
		
		void printPoints(){
			cout<<"point: ";
			for(int j = 0; j < dimensionNum; j++) cout<<*(point + j)<<" ";
			cout<<endl;
			
			cout<<k<<" nearest"<<endl;
			for(int i = 0; i < count; i++){
				cout<<*(distances + i)<<":";
				for(int j = 0; j < dimensionNum; j++) cout<<*(points + dimensionNum * i + j)<<" ";
				cout<<endl;
			}
			cout<<"----------------------"<<endl;
		}
		
		~KNearest(){
			delete[] points;
			delete[] distances;
		}
	
};

class KDTree{

	public:
		KDNode *dummyNode = nullptr;
		KDNode *root = nullptr;
		int dimensionNum;
		int size;
		int *data;
		int *copyBuffer;
		
		void swap(int *a, int *b, int dimensionNum){
			memcpy(copyBuffer, a, sizeof(int)*dimensionNum);
			memcpy(a, b, sizeof(int)*dimensionNum);
			memcpy(b, copyBuffer, sizeof(int)*dimensionNum);
		}
		
		//按照某一个维度的中位数进行划分，调用partition完成
		void partitionByMedian(int *data, int size, int dimension){
			//cout<<"partitionByMedian"<<data<<" "<<size<<" "<<dimension<<endl;
			int medianPos = size/2;
			int left, right, partitionPos;
			left = 0, right = size - 1;
			while(left < right){
				//cout<<"while "<<left<<" "<<right<<" "<<medianPos<<" "<<dimension<<endl;

				partitionPos = partitionByDimension(data + left*dimensionNum, right - left + 1, dimension) + left;
				//cout<<"partitionPos "<<partitionPos<<endl;
				if(partitionPos == medianPos) break;
				else if(partitionPos > medianPos){
					right = partitionPos - 1;
				}else{
					left = partitionPos + 1;
				}

				
			}
		} 
		
		int partitionByDimension(int *data, int size, int dimension){
			//cout<<"partitionByDimension"<<data<<" "<<size<<" "<<dimension<<endl;
			int left = 0;
			//printData(data, size);
			for(int i = 0; i < size - 1; i++){
				if(*(data + i*dimensionNum + dimension) < *(data + (size - 1)*dimensionNum + dimension)){
					//cout<<"swap "<<left<<" "<<i<<endl;
					swap(data + left*dimensionNum, data + i*dimensionNum, dimensionNum);  
					left++;
				} 
			}
			//cout<<"swap "<<left<<" "<<(size - 1)<<endl;
			swap(data + left*dimensionNum, data + (size - 1)*dimensionNum, dimensionNum);
			//printData(data, size);
			return left;
		}
		



		KDTree(int *data, int dimensionNum, int size){
			this->data = data;
			this->dimensionNum = dimensionNum;
			this->size = size;
			

			copyBuffer = new int[dimensionNum];
			dummyNode = new KDNode(dimensionNum, 0,0,nullptr);
			root = dummyNode;
		}
			
		void buildTree(){
			int *limit = new int[2*dimensionNum];
			for(int i = 0; i < dimensionNum; i++){
				*(limit + i*2) = MIN;
				*(limit + i*2 + 1) = MAX;
			}
			
			root = buildTree(data, size, 0, limit);
			delete limit;
		}

		KDNode* buildTree(int *data, int size, int dimension, int *limit){
			//cout<<data<<" "<<size<<" "<<dimension<<endl;
			if(size == 0) return dummyNode;
			if(size == 1)  {
				//cout<<"size 1 insert"<<*(data)<<*(data+1)<<endl;
				KDNode *cur = new KDNode(dimensionNum, dimension, *(data + dimension), data);
				cur->left = dummyNode;
				cur->right = dummyNode;
				memcpy(cur->limit, limit, sizeof(int)*dimensionNum*2);
				return cur;
			}
			
			int medianPos = size/2;
			partitionByMedian(data, size, dimension);
			//cout<<"\n\npartition "<<medianPos<<" "<<*(data + medianPos*dimensionNum + dimension)<<endl;
			//printData(data, size);
			KDNode *cur = new KDNode(dimensionNum, dimension, *(data + medianPos*dimensionNum + dimension), data + medianPos*dimensionNum);
			memcpy(cur->limit, limit, sizeof(int)*dimensionNum*2);
			
			//保存用于函数结束时恢复limit，用于别的分支使用 
			int tUpper = *(limit + dimension*2 + 1);
			int tlower = *(limit + dimension*2);
			 
			*(limit + dimension*2 + 1) = *(data + medianPos*dimensionNum + dimension);
			KDNode *left = buildTree(data, medianPos, (dimension + 1)%dimensionNum, limit);
			*(limit + dimension*2 + 1) = tUpper;
			
			*(limit + dimension*2) = *(data + medianPos*dimensionNum + dimension);
			KDNode *right = buildTree(data + (medianPos+1)*dimensionNum, size - medianPos - 1, (dimension + 1)%dimensionNum, limit);
			*(limit + dimension*2) = tlower; 
			
			//cout<<"insert"<<*(data + medianPos*dimensionNum)<<*(data + medianPos*dimensionNum+1)<<endl;
			cur->left = left;
			cur->right = right;
			return cur;
		}
		
		KNearest searchTree(int *point, int k){
			KNearest nearestPoints(point, dimensionNum, k);
			searchNode(root, &nearestPoints,0);
			return nearestPoints;
		}
		
		void searchNode(KDNode *curNode, KNearest *nearestPoints, int dimension){
			KDNode *nextNode = nullptr;
			KDNode *otherNode = nullptr;
//			cout<<"search"<<endl;
//			curNode->print();
//			cout<<"------"<<endl;
			
			if(nearestPoints->smallerThanMedian(curNode)){
				nextNode = curNode->left;
				otherNode = curNode->right;
			}else{
				nextNode = curNode->right;
				otherNode = curNode->left;
			}
			
			if(nextNode != dummyNode){
				searchNode(nextNode, nearestPoints, (dimension + 1)%dimensionNum);
			}
			
			nearestPoints->tryInsertPoint(curNode->data);
			
			if(otherNode != dummyNode && nearestPoints->intersectWith(otherNode)){
				searchNode(otherNode, nearestPoints, (dimension + 1)%dimensionNum);
			}
		}
		
		void printTree(){
			printNode(root);
		}
		
		void printNode(KDNode *node){
			if(node == dummyNode) return;
			node->print();
			if(node->left != dummyNode) printNode(node->left);
			if(node->right != dummyNode) printNode(node->right);
		}
		
		void printData(int *data, int size){
			for(int i = 0; i < dimensionNum; i++){
				for(int j = 0; j < size; j++){
					//cout<<*(data + j*dimensionNum + i)<<" ";
				}
				//cout<<endl;
			}
		}
		
		printKNearest(int *point, int k){
			cout<<"getWithLinerSort"<<endl;
			KNearest nearestPoints(point, dimensionNum, k);
			for(int i = 0; i < size; i++){
				nearestPoints.tryInsertPoint(data + i*dimensionNum);
			}
			nearestPoints.printPoints();
		} 
		
		~KDTree(){
			if(root != nullptr) delete root;
			if(dummyNode != nullptr) delete dummyNode;
			if(copyBuffer != nullptr) delete copyBuffer;
		}
};





int main(){
	srand(time(0));
	int dimensionNum = 6;
	int size = 100;
	int *data = new int[dimensionNum*size];
	for(int i = 0; i < dimensionNum*size; i++) *(data + i) = random(100);
	// for(int i = 0; i < dimensionNum; i++){
		// for(int j = 0; j < size; j++){
			// cout<<*(data + j*dimensionNum + i)<<" ";
		// }
		// cout<<endl;
	// }
	for(int i = 0; i < size; i++){
		for(int j = 0; j < dimensionNum; j++){
			cout<<*(data + i*dimensionNum + j)<<" ";
		}
		cout<<endl;
	}
	cout<<"-------------------------------"<<endl;
	KDTree *kdTree = new KDTree(data, dimensionNum, size);
	kdTree->buildTree();
	kdTree->printTree();
	int *points = new int[dimensionNum];
	for(int i = 0; i < dimensionNum; i++) *(points + i) = random(100);
	
	cout<<"-------------------------------"<<endl;
	KNearest && nearest = kdTree->searchTree(points, 3); 
	nearest.printPoints();
	
	cout<<"-------------------------------"<<endl;
	kdTree->printKNearest(points, 4);
	delete kdTree;
	delete[] data;
	return 0;
}
