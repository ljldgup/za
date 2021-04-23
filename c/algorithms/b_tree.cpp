/************************************************************************
    > File Name: b_tree.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月22日 15:01:09
************************************************************************/

#include<iostream>
#include<vector>
#include<ctime>
using namespace std;
#define random(x) (rand()%(x+1))

int depth = 0;
int count = 0;

struct BTreeNode{
	bool isLeaf;
	int size;
	int *keys;
	BTreeNode **children;
	BTreeNode(int d){
		this->size = 0;
		keys = new int[2*d - 1]();
		children = new BTreeNode*[2*d]();
	}
	~BTreeNode(){
		delete keys;
		//注意这里不需要delete子孩指针，有外部函数递归操作就可以了
		// for(int i = 0; i< size + 1;i++){
			// delete *(children + i);
		// }
		delete children;
	}
};

class BTree{
	public:
		int degree;
		BTree(int d);
		~BTree();
		void insert(int key);
		
		BTreeNode* search(int key);
		void release(BTreeNode* node);
		void remove(int key);
		void print();
		void printInOrder(BTreeNode* node);
		void printByNode(BTreeNode* node);
	private:
		void remove(BTreeNode* node, int key);
		void ajust(BTreeNode* node, int pos);
		void splitChild(BTreeNode* node ,int pos);
		void insertNotFull(BTreeNode* node, int key);
		BTreeNode* root;
		unsigned int size;
};

BTree::BTree(int d){
	this->degree = d;
	root = new BTreeNode(2*d-1);
	//初始华的时候根为叶
	root->isLeaf = true;
	size = 0;
}


BTree::~BTree(){
	count = 0;
	release(root);
}


void BTree::release(BTreeNode *node){
	// cout<<node<<" "<<count++<<endl;
	if(node != nullptr){
		// cout<<"enter loop"<<endl;

		for(int i = 0; i < node->size + 1;i++){
			release(*(node->children + i));
		}
	}
	//delete会调用node内部的析构，释放空间
	delete node;
}

BTreeNode* BTree::search(int key){
	BTreeNode *node = root;
	// cout<<"search "<<key<<endl;
	int i = 0;
	while(node != nullptr){
		i = 0;
		while(i < node->size && *(node->keys + i) < key ) {
			i++;
			// cout<<*(node->keys + i)<<" ";
		}
		// cout<<endl;
		//没有找到key
		if( i == node->size || *(node->keys + i) > key) {
			// 打印搜索区间
			// cout<<"search "<<node<<" "<<node->size<<" ";
			// if(i == 0){
				// cout<<"-∞,"<<*(node->keys + i)<<endl;
			// }else if(i == node->size){
				// cout<<*(node->keys + i - 1)<<",+∞"<<endl;
			// }else{
				// cout<<*(node->keys + i - 1)<<","<<*(node->keys + i)<<endl;
			// }
			node = *(node->children + i);
			//cout<<"search "<<node<<" "<<node->size<<" ";
		}else{
			cout<<"找到"<<key<<endl;
			return node;
		}
	}
	
	cout<<"未找到"<<key<<endl;
	return nullptr;
}

//x父节点，y分裂节点，z分裂出的y右侧节点
void BTree::splitChild(BTreeNode* x, int pos){
	//cout<<"splitChild:"<<x<<" pos:"<<pos<<endl;
	BTreeNode* z = new BTreeNode(2*degree - 1);
	BTreeNode* y = *(x->children + pos);
	int midPos = y->size/2;
	int midKey = *(y->keys + midPos);

	z->isLeaf = y->isLeaf;
	for(int i = x->size; i > pos; i--){
		*(x->keys + i) = *(x->keys + i - 1);
		*(x->children + i + 1) = *(x->children + i);
	}
	*(x->keys + pos) = midKey;
	*(x->children + pos + 1) = z;
	x->size++;

	for(int i = midPos + 1; i < y->size; i++){
		*(z->keys + i - midPos -1) = *(y->keys + i);
	}

	for(int i = midPos + 1; i < y->size + 1; i++){
		*(z->children + i - midPos - 1) = *(y->children + i);
	}

	z->size = y->size - midPos - 1;
	y->size = midPos;
	//print();
}

void BTree::insert(int k){
	size++;
	//cout<<"insert "<<k<<endl;
	BTreeNode* node = root;
	if(node->size == 2*degree - 1){
		BTreeNode* s = new BTreeNode(degree);
		root = s;
		s->isLeaf = false;
		*s->children = node;
		splitChild(s, 0);
		insertNotFull(s, k);
	}else{
		insertNotFull(node, k);
	}
}

void BTree::remove(int key){
	BTreeNode* node = search(key);
	BTreeNode* preNode = nullptr;
	
	if(node == nullptr){
		cout<<key<<"不存在"<<endl;
		return;
	}
	
	int i = 0;
	while(node != nullptr){
		if(node->size < degree) ajust(preNode, i);
		
		i = 0;
		while(i < node->size && *(node->keys + i) < key ) i++;
		
		//不存在,查找下一个
		if( i == node->size || *(node->keys + i) > key) 
			
		{	
			preNode = node;
			node = *(preNode->children + i);
		}
		else break;
	}
	
	remove(node, i);
	size--;
}


//针对算法导论3的情况对x.ci进行调整
void BTree::ajust(BTreeNode* x, int pos){
	cout<<"ajust"<<endl;
	BTreeNode* left = *()
	
}


void BTree::remove(BTreeNode* x, int pos){
	BTreeNode* left;
	BTreeNode* right;
	left = *(x->children + pos);
	right = *(x->children + pos + 1);
	if(x->isLeaf){
		for(int i = pos; i < x->size - 1; i++){
			*(x->keys + i) = *(x->keys + i + 1);
			*(x->children + i + 1) = *(x->children + i + 2);
		}
		x->size--;
	}
	else if(left->size > degree - 1){
		//左侧最右边节点上移,再递归
		*(x->keys + pos) = *(left->keys + left->size - 1);
		remove(left, left->size-1);
	}
	else if(right->size > degree - 1){
		//右侧最左边节点上移，再递归
		*(x->keys + pos) = *(right->keys);
		remove(right, 0);
	}
	else{
		//删除key下移,合并左右， 再递归
		*(left->keys + left->size) = *(x->keys + pos);	
		for(int i = 0; i < right->size; i++){
			*(left->keys + left->size + i) = *(right->keys + i);
			*(left->children + left->size + i + 1) = *(right->children + i);
		}
		*(left->children + left->size + right->size) = *(right->children + right->size);
		left->size += right->size + 1;
		delete right;
		
		//当前节点删除key
		for(int i = pos; i < x->size - 1; i++){
			*(x->keys + i) = *(x->keys + i + 1);
			*(x->children + i + 1) = *(x->children + i + 2);
		}
		x->size--;
		
		//合并后总长2*degree-1, key位于中间
		remove(left, degree - 1);
	}
}


void BTree::insertNotFull(BTreeNode* x, int k){
	//cout<<"insert not full:"<<x<<" key:"<<k<<endl;
	int i;
	BTreeNode* child;
	if(x->isLeaf){
		i = x->size;
		while(i >= 1 && *(x->keys + i - 1) > k) {
			*(x->keys + i) = *(x->keys + i - 1);
			i--;
		}
		*(x->keys + i) = k;
		x->size += 1;
	}
	else{
		i = x->size - 1;
		//注意这个循环对于最左侧节点也有效
		while(i >= 0 && *(x->keys + i) > k) i--;
		child = *(x->children + i + 1);
		if(child->size == 2*degree - 1){
			splitChild(x, i+1);
			//分裂后新增关键字小于k，则k对应的区间后移一个
			if(*(x->keys + i + 1) < k) i++;
		}
		insertNotFull(*(x->children + i + 1), k);
	}
}

void BTree::print(){
	count = 0;
	printInOrder(root);
	cout<<endl<<"记录数量"<<size<<",实际打印数量"<<count<<endl;
	// count = 0;
	// printByNode(root);
	// cout<<endl<<"记录数量"<<size<<",实际打印数量"<<count<<endl;
	cout<<endl<<"------------------------------"<<endl;
}

void BTree::printInOrder(BTreeNode* node){
	depth++;
	if(node ==nullptr) return;
	
	//cout<<node<<" size:"<<node->size<<endl;
	
	int i;
	//cout<<" "<<node<<"("<<node->size<<")"<<":";
	for(i = 0; i < node->size;i++){
		if(!node->isLeaf) printInOrder(*(node->children + i));
		count++;
		//cout<<"深度"<<depth<<",计数"<<count<<":"<<*(node->keys + i)<<"  ";
		cout<<*(node->keys + i)<<" ";
	}
	//cout<<";";
	if(!node->isLeaf) printInOrder(*(node->children + i));
	//cout<<endl;
	depth--;
}

void BTree::printByNode(BTreeNode* node){
	depth++;
	if(node == nullptr) return;
	cout<<node<<" 深度:"<<depth<<", 数量:"<<node->size<<" ";
	for(int i = 0; i < node->size; i++){
		count++;
		cout<< *(node->keys + i) << " ";
	}
	cout<<endl;
	if(!node->isLeaf){
		for(int  i = 0; i < node->size + 1; i++){
			printByNode(*(node->children + i));
		}
	}
	depth--;
}



int main(){
	BTree btree(4);
	
	for(int i = 0; i < 1000; i++){
		btree.insert(i);
	}
	
	for(int i = 0; i < 10; i++){
		//btree.search(random(2000));
		btree.remove(random(2000));
	}
	
	btree.print();
	return 1;
}
