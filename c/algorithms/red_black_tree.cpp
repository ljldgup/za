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
#include<tuple>
#include<set>  
using namespace std;
#define random(x) (rand()%(x+1))

#define OUT_BLACK   "\033[30m"      /* Black */
#define OUT_RED     "\033[31m"      /* Red */

enum color{
	RED,BLACK
};

class TreeNode{
	public:
		color c;
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
		TreeNode* maximum(TreeNode* n);
		TreeNode* minimum(TreeNode* n);
		TreeNode* search(int value);
		
		void leftRotate(TreeNode* n);
		void rightRotate(TreeNode* n);
		
		void insert(TreeNode* n);
		void insertFixUp(TreeNode* n);
		
		void transplant(TreeNode* u, TreeNode* v);	
		void remove(TreeNode* n);
		void removeFixUp(TreeNode* n);
		
		void validate();
		void print();
		void print(TreeNode* node);
		void print_level();
		int getHeight();
		int getSize();
		bool isNil(TreeNode* node);
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


TreeNode* BlackRedTree::minimum(TreeNode *node){
	while(node->left != nil){
		// cout<<node->value<<" ";
		node = node->left;
	}
	return node;
}

TreeNode* BlackRedTree::maximum(TreeNode *node){
	while(node->right != nil){
		// cout<<node->value<<" ";
		node = node->right;
	}
	return node;
}

TreeNode* BlackRedTree::search(int value){
	TreeNode* node = root;
	//cout<<"搜索:"<<value<<endl;
	//cout<<"途径 ";
	while(node != nil){
		//cout<<node->value<<" ";
		if(node->value == value)  break;
		if(node->value > value) node = node->left;
		else node = node->right;
	}
	if(node->value != value){
		cout<<"未找到"<<value<<endl;
		return nil;
	}
	//cout<<"找到"<<value<<endl;
	return node;
}

void BlackRedTree::rightRotate(TreeNode* n){
	//cout<<"rightRotate "<<n->value<<endl;
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
	n->left->p = n;
	m->right = n;
	//print_level();
		
}

void BlackRedTree::leftRotate(TreeNode* n){
	//cout<<"leftRotate "<<n->value<<endl;
	if(n->right == nil) return;
	TreeNode* m = n->right;
	
	if(n == root){
		root = m;
	}else if(n == n->p->left) n->p->left = m;
	else if(n == n->p->right) n->p->right = m;
	m->p = n->p;
	n->p = m;
	
	n->right = m->left;
	n->right->p = n;
	m->left = n;
	//print_level();
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
				// n父，n父兄均为红，无法旋转，染色后向上循环
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

//使用y节点替换x节点
void BlackRedTree::transplant(TreeNode* x, TreeNode* y){

	if(x == root){
		root = y;
	}
	else if(x == x->p->left){
		x->p->left = y;
	}else{
		x->p->right = y;
	}
	//这里不能加这个判断，因为nil也会进入removefixup，这样就造成了无法找到父节点。
	//if(y != nil) 
	y->p = x->p;
}



void BlackRedTree::remove(TreeNode* n){
	//y记录了删除后，树结构发生变化的点
	//x记录替代y的节点
	TreeNode* x;
	TreeNode* y = n;
	color y_ori_color = n->c;
	
	if(n->left == nil){
		x = n->right;
		transplant(n, n->right);
	}
	else if(n->right == nil){
		x = n->left;
		transplant(n, n->left);
	}else{
		y = minimum(n->right);
		y_ori_color = y->c;
		x = y->right;
		if(y->p == n){
			x->p = y;
		}
		else{
			transplant(y, y->right);
			y->right = n->right;
			y->right->p = y;
		}
		transplant(n, y);
		y->left = n->left;
		y->left->p = y;
		y->c = n->c;
	}
	
	if(y_ori_color == BLACK){
		removeFixUp(x);
	}
	delete n;
	size--;
}

void BlackRedTree::removeFixUp(TreeNode* x){
	//cout<<"removeFixUp "<< x->value<<endl<<"x->p "<<x->p->value<<endl;
	//print_level();
	while(x != root && x->c == BLACK){
		if(x == x->p->left){
			TreeNode* w = x->p->right;
			if(w->c == RED){
				w->p->c = RED;
				w->c = BLACK;
				leftRotate(x->p);
				//旋转为x父的右节点，实际是旧w的子节点，旧w为红，新w为黑
				w = x->p->right;
			}
			if(w->left->c == BLACK && w->right->c == BLACK){
				w->c = RED;
				x = x->p;
			}else {
				if(w->right->c == BLACK){
					//w内侧子孩为红，颜色互换后外旋,
					w->left->c = BLACK;
					w->c = RED;
					rightRotate(w);
					w = x->p->right;
				}
				w->c = x->p->c;
				x->p->c = BLACK;
				w->right->c = BLACK;
				leftRotate(x->p);
				x = root;
			}
		}
		else{
			TreeNode* w = x->p->left;
			if(w->c == RED){
				w->p->c = RED;
				w->c = BLACK;
				rightRotate(x->p);
				//旋转为x父的右节点，实际是旧w的子节点，旧w为红，新w为黑
				w = x->p->left;
			}
			if(w->right->c == BLACK && w->left->c == BLACK){
				w->c = RED;
				x = x->p;
			}else {
				if(w->left->c == BLACK){
					//w内侧子孩为红，颜色互换后外旋,
					w->right->c = BLACK;
					w->c = RED;
					leftRotate(w);
					w = x->p->left;
				}
				
				w->c = x->p->c;
				x->p->c = BLACK;
				w->left->c = BLACK;
				rightRotate(x->p);
				x = root;
			}
		}
	}
	//cout<<x<<endl;
	x->c = BLACK;
	//cout<<"removeFixUp "<< x->value<<endl<<"x->p "<<x->p->value<<endl;
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

bool BlackRedTree::isNil(TreeNode* n){
	return nil==n;
}

void BlackRedTree::validate(){
	queue<tuple<int, TreeNode*>> nodeQueue;
	set<int> blackHeigt;
	TreeNode *node;
	int length;
	
	nodeQueue.push(make_tuple(1, root));
	while(nodeQueue.size()>0){
		tuple<int, TreeNode*> t = nodeQueue.front();
		nodeQueue.pop();
		
		node = get<1>(t);
		length = get<0>(t);
		if(node->c == BLACK) length++;

		if(node->right == nil && node->left == nil){
			blackHeigt.insert(length);
			continue;
		} 
		
		if(node->left != nil){
			if(node->c == RED && node->left->c == RED ){
				cout<<node->value<<"处连续出现红色，违规"<<endl;
				print_level();
				return;
			}
			nodeQueue.push(make_tuple(length, node->left));
		}
		
		if(node->right != nil){
			if(node->c == RED && node->right->c == RED ){
				cout<<node->value<<"处连续出现红色，违规"<<endl;
				print_level();
				return;
			}
			nodeQueue.push(make_tuple(length, node->right));
		}
	}
	
	if(blackHeigt.size() != 1) {
		cout<<"黑高不相同,违规"<<endl;
	}else{
		cout<<"红黑树合规"<<endl;
	}
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
	TreeNode* node;

	int length;
	scanf("%d", &length);
	
	for(int i = length; i > 0; i--){
		brTree.insert(new TreeNode(i));
		//brTree.print_level();
		brTree.validate();
	}

	if(length < 20){
		//brTree.print();
		brTree.print_level();
	}

	cout<<"size "<<brTree.getSize()<<endl<<"height: "<<brTree.getHeight()<<endl;
	
	for(int i = 0; i < length; i+= 4){
		node =  brTree.search(i);
		if(!brTree.isNil(node)){
			brTree.remove(node);
			brTree.validate();
			//brTree.print();
			//brTree.print_level();
		}

	}
	cout<<"size "<<brTree.getSize()<<endl<<"height: "<<brTree.getHeight()<<endl;
	return 1;
}
