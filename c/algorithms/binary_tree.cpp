/************************************************************************
    > File Name: binary_node.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月10日 17:43:34
************************************************************************/

#include<iostream>
#include<queue>
#include<ctime>
using namespace std;
#define random(x) (rand()%(x+1))

class TreeNode{
	public:
		TreeNode* left;
		TreeNode* right;
		TreeNode* parent;
		int value;
		TreeNode(int v){
			value = v;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}
};

class BinaryTree{
	public:
		int size;
		BinaryTree();
		~BinaryTree();
		void insert(int value);
		TreeNode* minimum(TreeNode* node);
		TreeNode* maximum(TreeNode* node);
		TreeNode* successor(TreeNode* node);
		TreeNode* search(int value);
		void transplant(TreeNode* u, TreeNode* v);
		void remove(TreeNode* node);
		void print();
		void print(TreeNode* node);
		void print_level();
	private:
		TreeNode* root;
		void release(TreeNode *node);
};

BinaryTree::BinaryTree(){
	size = 0;
	root = nullptr;
}

BinaryTree::~BinaryTree(){
	release(root);
}

void BinaryTree::release(TreeNode *node){
	if(node != nullptr){
		release(node->left);
		release(node->right);
		// cout<<"realse "<<node->value<<',';
		delete node;
	}
}

TreeNode* BinaryTree::search(int value){
	TreeNode* node = root;
	while(node != nullptr){
		cout<<"search "<<node->value<<endl;
		if(node->value == value)  break;
		if(node->value > value) node = node->left;
		else node = node->right;
	}
	return node;
}

void BinaryTree::insert(int value){
	cout<<"insert:"<<value<<endl;
	if(root == nullptr){
		root = new TreeNode(value);
		size++;
		return;
	}
	
	TreeNode* node = root;
	TreeNode* parent = nullptr;
	
	while(node != nullptr){
		if(node->value == value) {
			cout<<"值重复"<<endl;
			return;
		}
		parent = node;
		if(node->value > value) node = node->left;
		else node = node->right;
	}
	
	TreeNode* tNode = new TreeNode(value);
	if(parent->value > value){
		parent->left = tNode;
		tNode->parent = parent;
	}
	else{
		parent->right = tNode;
		tNode->parent = parent;
	}
	size++;
}

//使用y节点替换x节点
void BinaryTree::transplant(TreeNode* x, TreeNode* y){

	//cout<<"transplant"<<x<<" "<<y<<endl;
	if(x == root){
		root = y;
	}
	else if(x == x->parent->left){
		x->parent->left = y;
		//cout<<"x->parent->left"<<y<<" "<<y<<endl;
	}else{
		x->parent->right = y;
		//cout<<"x->parent->right"<<y<<" "<<y<<endl;
	}
	if(y != nullptr) y->parent = x->parent;
}

//这里只是返回当前节点为根的最大值
void BinaryTree::remove(TreeNode *node){
	if(node->left == nullptr){
		transplant(node, node->right);
	}else if(node->right == nullptr){
		transplant(node, node->left);
	}else{
		TreeNode* y = minimum(node->right);
		
		if(y->parent != node){
			//y的左侧节点肯定为空
			transplant(y, y->right);
			y->right = node->right;
			y->right->parent = y;
		}
		transplant(node, y);
		y->left = node->left;
		y->left->parent = y;
	}
}

TreeNode* BinaryTree::minimum(TreeNode *node){
	while(node->left != nullptr){
		// cout<<node->value<<" ";
		node = node->left;
	}
	return node;
}

TreeNode* BinaryTree::maximum(TreeNode *node){
	while(node->right != nullptr){
		// cout<<node->value<<" ";
		node = node->right;
	}
	return node;
}

TreeNode* BinaryTree::successor(TreeNode* x){
	if(x->right != nullptr){
		return minimum(x->right);
	}
	
	TreeNode* y = x->parent;
	while(y != nullptr && x == y->right){
		x = y;
		y = y->parent;
	}
	return y;
}

void BinaryTree::print(){
	print(root);
	cout<<endl;
}

void BinaryTree::print(TreeNode* node){
	if(node != nullptr){
		print(node->left);
		cout<<node->value<<' ';
		print(node->right);
	}
}
void BinaryTree::print_level(){
	//广度优先进行打印效果一般
	queue<TreeNode*> nodeQueue;
	int tCount, count, length, interval;
	TreeNode* tNode;
	
	count = 1;
	tCount = 0;
	length = 1;
	//因为是整数太小效果和预期的差很多
	interval  = (100 - length)/(length + 1);
	nodeQueue.push(root);
	while(count>0){
		// cout<<interval<<endl;
		tCount = 0;
		
		
		for(int i = 0; i < length; i++){
			//每层间隔为2^(n-1)+1个，间隔长度为(size-2^(n-1))/(2^(n-1)-1)
			for(int j = 0; j < interval - 1; j++){
				cout<<' ';
			}
			tNode = nodeQueue.front();
			nodeQueue.pop();
			if(tNode != nullptr){
				tCount++;
				cout<<tNode->value;
				nodeQueue.push(tNode->left);
				nodeQueue.push(tNode->right);
			}else{
				cout<<' ';
				nodeQueue.push(nullptr);
				nodeQueue.push(nullptr);
			}
		}
		for(int j = 0; j < interval; j++){
			cout<<' ';
		}
		cout<<endl;
		length *= 2;
		interval  = (100 - length)/(length + 1);
		count = tCount;
	}
}

int main(){
	srand(time(0));
	BinaryTree tree;
	int length = random(20);
	for(int i = 0; i < length; i++){
		cout<<i<<' ';
		tree.insert(random(length));
	}
	
	tree.print();
	tree.print_level();
	
	int x = length/3;
	cout<<"x:"<<x<<endl;
	TreeNode *n = tree.search(x);
	if(n != nullptr){
			cout<<"n:"<<n->value<<endl;
			cout<<"left "<<n->left<<endl;
			cout<<"right "<<n->right<<endl;
			cout<<"parent "<<n->parent<<endl;
			cout<<"maximum"<<tree.maximum(n)->value<<endl;
			cout<<"minimum"<<tree.minimum(n)->value<<endl;
			cout<<"successor"<<tree.successor(n)->value<<endl;
			tree.remove(n);
			tree.print();
	}
	else{
		cout<<"does not find "<<x<<endl;
	}

}
