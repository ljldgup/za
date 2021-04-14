/************************************************************************
    > File Name: red_black_tree.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月14日  8:52:45
************************************************************************/

#include<iostream>
#include<vector>
#include<ctime>
#include<queue>
using namespace std;
#define random(x) (rand()%(x+1))

#define OUT_BLACK   "\033[30m"      /* Black */
#define OUT_RED     "\033[31m"      /* Red */

enum colors{
	RED,BLACK
};

class TreeNode{
	public:
		colors c;
		int value;
		TreeNode* p;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int v);
};

TreeNode::TreeNode(int v){
	value = v;
	c = RED;
}

class BlackRedTree{
	public:
		BlackRedTree();
		~BlackRedTree();
		void leftRotate(TreeNode* n);
		void rightRotate(TreeNode* n);
		void insert(TreeNode* n);
		void remove(TreeNode* n);
		void insertFixUp(TreeNode* n);
		void removeFixUp(TreeNode* n);
		void print();
		void print(TreeNode* node);
		void print_level();
		int getHeight();
		int getSize();
	private:
		TreeNode* root;
		TreeNode* nil;
		int size;
		void release(TreeNode* node);
};

BlackRedTree::BlackRedTree(){
	nil = new TreeNode(-137946285);
	nil->c = BLACK;
	root = nil;
	size = 0;
}

BlackRedTree::~BlackRedTree(){
	release(root);
	delete nil;
}

void BlackRedTree::release(TreeNode* node){
	if(node == nil) return;
	else{
		release(node->left);
		release(node->right);
		delete node;
	}
}

void BlackRedTree::rightRotate(TreeNode* n){
	if(n->left == nil) return;
	TreeNode* m = n->left;
	
	//取父节点时先排除根节点
	if(n == root){
		root = m;
	}
	else if(n == n->p->left) n->p->left = m;
	if(n == n->p->right) n->p->right = m;
	m->p = n->p;
	n->p = m;
	
	n->left = m->right;
	m->right = n;
		
}

void BlackRedTree::leftRotate(TreeNode* n){
	if(n->right == nil) return;
	TreeNode* m = n->right;
	
	if(n == root){
		root = m;
	}else if(n == n->p->left) n->p->left = m;
	else if(n == n->p->right) n->p->right = m;
	m->p = n->p;
	n->p = m;
	
	n->right = m->left;
	m->left = n;
}


void BlackRedTree::insert(TreeNode* n){

	//cout<<"insert "<<n->value<<endl;
	TreeNode* y = nil;
	TreeNode* x = root;
	n->c = RED;
	n->left = nil;
	n->right = nil;
	
	while(x != nil){

		if(x->value == n->value){
			cout<<"值重复:"<<n->value<<endl;
		}
		
		y = x;
		if(x->value > n->value){
			x = x->left;
		}else{
			x = x->right;
		}
	}
	size++;
	if(y == nil) {
		root = n;
		root->p = nil;
		//这里不能return，根节点也需要fix，设置为黑
		//return;
	}
	
	if(y->value > n->value){
		n->p = y;
		y->left = n;
	}else{
		n->p = y;
		y->right = n;
	}
	//print_level();
	insertFixUp(n);
	//print_level();
}

void BlackRedTree::insertFixUp(TreeNode* n){
	TreeNode* y;
	//cout<<"FIX UP "<< n->value<<endl;
	//int depth = 0;
	while(n->p->c == RED){
		//cout<<"loop "<<n->value<<" "<<n->p->value<<endl;
		//if(depth++ > 10) return;

		if(n->p == n->p->p->left){
			y = n->p->p->right;
			if(y->c == RED){
				//cout<<"left case 1"<<endl;
				y->c = BLACK;
				n->p->c = BLACK;
				n->p->p->c = RED;
				n = n->p->p;
			}
			else {
				if(n == n->p->right){
					//cout<<"left case 2"<<endl;
					n = n->p;
					leftRotate(n);
				}
				
				n->p->c = BLACK;
				n->p->p->c = RED;
				rightRotate(n->p->p);	
				
			}
		}
		else{
			y = n->p->p->left;
			//cout<<y->value<<" "<<y->c<<endl;
			if(y->c == RED){
				//cout<<"right case 1"<<endl;
				y->c = BLACK;
				n->p->c = BLACK;
				n->p->p->c = RED;
				n = n->p->p;
			}
			else {
				if(n == n->p->left){
					//cout<<"right case 2"<<endl;
					n = n->p;
					rightRotate(n);
				}
				n->p->c = BLACK;
				n->p->p->c = RED;
				leftRotate(n->p->p);
			}
			//cout<<"loop end"<<n->value<<" "<<n->c<<" "<<n->p->value<<endl;
		}
	}
	root->c=BLACK;
}

void BlackRedTree::remove(TreeNode* n){
	
}

void BlackRedTree::removeFixUp(TreeNode* n){

}

int BlackRedTree::getHeight(){
	TreeNode* node = root;
	vector<TreeNode*> nodeList1;
	vector<TreeNode*> nodeList2;
	int height = 0;
	
	nodeList1.push_back(root);
	while(nodeList1.size()>0){
		height++;
		for(auto node:nodeList1){
			//cout<<node->value<<' ';
			if(node->left != nil){
				nodeList2.push_back(node->left);
			}
			if(node->right != nil){
				nodeList2.push_back(node->right);
			}
		}
		//cout<<node->value<<endl;
		nodeList1.swap(nodeList2);
		nodeList2.clear();
	}
	return height;
}

int BlackRedTree::getSize(){
	return size;
}

void BlackRedTree::print(){
	print(root);
	cout<<endl;
}

void BlackRedTree::print(TreeNode* node){
	if(node != nil){
		print(node->left);
		cout<<node->value<<' ';
		print(node->right);
	}
}

void BlackRedTree::print_level(){
	//广度优先进行打印效果一般
	queue<TreeNode*> nodeQueue;
	int tCount, count, length, interval;
	TreeNode* tNode;
	char color;
	count = 1;
	tCount = 0;
	length = 1;
	//因为是整数太小效果和预期的差很多
	interval  = (100 - 6*length)/(length + 1);
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
	
			if(tNode != nil){
				tCount++;
				//红黑树颜色
				color = tNode->c == RED ? 'R':'B';
				cout<<tNode->value<<" "<<tNode->p->value<<" "<<color<<" ";
				nodeQueue.push(tNode->left);
				nodeQueue.push(tNode->right);
			}else{
				cout<<' ';
				nodeQueue.push(nil);
				nodeQueue.push(nil);
			}
		}
		for(int j = 0; j < interval; j++){
			cout<<' ';
		}
		cout<<OUT_BLACK<<endl;
		length *= 2;
		interval  = (100 - length)/(length + 1);
		count = tCount;
	}
}


int main(){
	BlackRedTree brTree;
	
	int length;
	scanf("%d", &length);
	
	for(int i = length; i > 0; i--){
		brTree.insert(new TreeNode(i));
	}

	if(length < 20){
		brTree.print();
		//brTree.print_level();
	}

	cout<<"size "<<brTree.getSize()<<endl<<"height: "<<brTree.getHeight()<<endl;
	return 1;
}
