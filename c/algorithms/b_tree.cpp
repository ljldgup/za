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
		void remove(BTreeNode* node);
		void search(int key);
		void release(BTreeNode* node);
		void print();
		void print_in_order(BTreeNode* node);
		void print_by_node(BTreeNode* node);
	private:
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

void BTree::search(int key){
	BTreeNode *node = root;
	cout<<"search "<<key<<endl;
	int i = 0;
	while(node != nullptr && *(node->keys + i) != key){
		i = 0;
		while(i < node->size && *(node->keys + i) < key ) i++;
		//或如果越界下一个条件不会走
		if( i == node->size || *(node->keys + i) > key) {
			cout<<"search "<<node<<" ";
			if(i == 0){
				cout<<"-∞,"<<*(node->keys + i)<<endl;
			}else if(i == node->size){
				cout<<*(node->keys + i - 1)<<",+∞"<<endl;
			}else{
				cout<<*(node->keys + i - 1)<<","<<*(node->keys + i)<<endl;
			}
			node = *(node->children + i);
		}else{
			cout<<"找到"<<key<<endl;
			return;
		}
	}
	
	cout<<"未找到"<<endl;
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
	//print_in_order(root);
	//cout<<endl<<"记录数量"<<size<<",实际打印数量"<<count<<endl;
	print_by_node(root);
	cout<<endl<<"------------------------------"<<endl;
}

void BTree::print_in_order(BTreeNode* node){
	depth++;
	if(node ==nullptr) return;
	
	//cout<<node<<" size:"<<node->size<<endl;
	
	int i;
	//cout<<" "<<node<<"("<<node->size<<")"<<":";
	for(i = 0; i < node->size;i++){
		if(!node->isLeaf) print_in_order(*(node->children + i));
		count++;
		//cout<<"深度"<<depth<<",计数"<<count<<":"<<*(node->keys + i)<<"  ";
		cout<<*(node->keys + i)<<" ";
	}
	//cout<<";";
	if(!node->isLeaf) print_in_order(*(node->children + i));
	//cout<<endl;
	depth--;
}

void BTree::print_by_node(BTreeNode* node){
	depth++;
	if(node == nullptr) return;
	cout<<node<<" 深度:"<<depth<<", 数量:"<<node->size<<" ";
	for(int i = 0; i < node->size; i++){
		cout<< *(node->keys + i) << " ";
	}
	cout<<endl;
	if(!node->isLeaf){
		for(int  i = 0; i < node->size + 1; i++){
			print_by_node(*(node->children + i));
		}
	}
	depth--;
}



int main(){
	BTree btree(4);
	
	for(int i = 0; i < 1000; i++){
		btree.insert(random(10000));
	}
	
	btree.print();
		
	for(int i = 0; i < 10; i++){
		btree.search(random(10000));
	}


	return 1;
}
