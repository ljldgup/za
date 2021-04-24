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
		//注意这里不需要delete子孩指针，因为子孩指针还指向子孩的子孩，
		//有外部函数递归操作就可以了
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
		void check();
	private:
		void removeChild(BTreeNode* node, int pos);
		void merge(BTreeNode* node, int pos);
		void leftRotate(BTreeNode* node, int pos);
		void rightRotate(BTreeNode* node, int pos);
		void remove(BTreeNode* preNode, int prePos, BTreeNode* node, int key);
		int ajust(BTreeNode* node, int pos);
		void splitChild(BTreeNode* node ,int pos);
		void insertNotFull(BTreeNode* node, int key);
		void check(BTreeNode* node);
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
	//delete会调用node内部的析构，释放空间,不需要再释放
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
			//cout<<"找到"<<key<<endl;
			return node;
		}
	}
	
	//cout<<"未找到"<<key<<endl;
	return nullptr;
}

//x父节点，y分裂节点，z分裂出的y右侧节点
//将y的中间节点上移，然后y右侧内容移入新建节点z中，z左右上移关键字右侧子孩
void BTree::splitChild(BTreeNode* x, int pos){
	//cout<<"splitChild:"<<x<<" pos:"<<pos<<endl;
	BTreeNode* z = new BTreeNode(2*degree - 1);
	BTreeNode* y = *(x->children + pos);
	int midPos = y->size/2;
	int midKey = *(y->keys + midPos);

	//注意叶节点属性要保持
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

//先看根目录是否需要分裂
void BTree::insert(int k){
	cout<<"insert "<<k<<endl;
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

//插入非根目录，搜索到叶节点再插入，搜索途径满的节点进行分裂。
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

//将当前父节点关键字左右俩孩合并，将关键字下移
//splitChild的相反操作
void BTree::merge(BTreeNode* node, int pos){
	// cout<<"merge "<<node<<" pos "<<pos<<" "<<*(node->children + pos)<<endl;
	BTreeNode* left;
	BTreeNode* right;
	left = *(node->children + pos);
	right = *(node->children + pos + 1);
	*(left->keys + left->size) = *(node->keys + pos);	
	for(int i = 0; i < right->size; i++){
		*(left->keys + left->size + i + 1) = *(right->keys + i);
		*(left->children + left->size + i + 1) = *(right->children + i);
	}
	*(left->children + left->size + right->size + 1) = *(right->children + right->size);
	left->size =left->size + right->size + 1;
	delete right;
	
	// for(int i = 0; i < left->size; i++)cout<<" "<<*(left->keys + i);
	// cout<<endl;
	// for(int i = 0; i < left->size + 1; i++)cout<<left->children + i<<" ";
	// cout<<endl;
	
	//当前节点删除key
	for(int i = pos; i < node->size - 1; i++){
		*(node->keys + i) = *(node->keys + i + 1);
		*(node->children + i + 1) = *(node->children + i + 2);
	}
	node->size--;
}

void BTree::leftRotate(BTreeNode* node, int pos){
	// cout<<"leftRotate "<<node<<" pos "<<pos<<" "<<*(node->children + pos)<<endl;
	
	BTreeNode* left = *(node->children + pos);
	BTreeNode* right = *(node->children + pos + 1);
	
	// cout<<"leftRotate left:"<<left<<" right:"<<right<<endl;
	//将支点关键字移到左侧，将右节点内侧（第一个）的子孩放到左侧节点内侧
	*(left->keys + left->size) = *(node->keys + pos);
	*(left->children + left->size + 1) = *(right->children);
	left->size++;
	
	//将右侧内侧（第一个）关键字 代替支点关键字
	*(node->keys + pos) = *(right->keys);
	
	//右节点缩减
	int i;
	for(i = 1; i < right->size ; i++){
		*(right->keys + i - 1) = *(right->keys + i);
		*(right->children + i - 1) = *(right->children + i);
	}
	*(right->children + i - 1) = *(right->children + i);
	right->size--;
}

void BTree::rightRotate(BTreeNode* node, int pos){
	// cout<<"rightRotate "<<node<<" pos "<<pos<<" "<<*(node->children + pos)<<endl;
	BTreeNode* left = *(node->children + pos);
	BTreeNode* right = *(node->children + pos + 1);
	//将支点关键字移到右子节点，将左子节点内侧（第一个）的子孩放到左侧节点内侧
	int i;
	for(i = right->size; i > 0 ; i--){
		*(right->keys + i) = *(right->keys + i - 1);
		*(right->children + i + 1) = *(right->children + i);
	}
	*(right->children + i + 1) = *(right->children + i);
	
	*(right->keys) = *(node->keys + pos);
	*(right->children) = *(left->children + left->size);
	right->size++;
	
	//将做侧内侧（第一个）关键字 代替支点关键字
	*(node->keys + pos) = *(left->keys + left->size - 1);
	
	//左节点缩减
	left->size--;
}

//针对算法导论3的情况对x.ci进行调整,对途径的节点宽度等于degree-1的通过旋转或合并加宽
//返回的整数用于重新定位key，返回-1则说明节点与前一个节点合并, 需要调整
int BTree::ajust(BTreeNode* node, int pos){
	
	BTreeNode *left, *cur, *right;

	int key;
	left = cur = right = nullptr;
	// cout<<"ajust "<<node<<" pos "<<pos<<" "<<*(node->children + pos)<<endl;
	
	if(pos > 0) left = *(node->children + pos - 1);
	cur = *(node->children + pos);
	if(pos < node->size) right = *(node->children + pos + 1);
	
	//判断兄弟节点数量，能否旋转
	//左旋
	if(right != nullptr && right->size >= degree){
		leftRotate(node, pos);
		return 0;
	}
	else if(left != nullptr && left->size >= degree) {
		rightRotate(node, pos - 1);
		return 1;
	}
	else{
		//此处需要父节点下移
		if(right != nullptr){
			merge(node, pos);
			return 0;
		}else{
			//合并当前节点+左侧节点，需要向右偏移degree-1+1
			merge(node, pos - 1);
			return -1;
		}
		
	}
}

void BTree::remove(int key){
	cout<<"remove "<<key<<endl;
	BTreeNode* node;
	BTreeNode* preNode;
	int prePos;
	int i;
	
	node = search(key);
	if(node == nullptr){
		cout<<key<<"不存在"<<endl;
		return;
	}
	
	i = 0;
	node = root;
	preNode = nullptr;
	while(node != nullptr){
		if(node!=root && node->size == degree - 1){
			int offset = ajust(preNode, prePos);
			if(offset == -1) {
				node = *(preNode->children + prePos - 1);
			}
		} 
		
		i = 0;
		while(i < node->size && *(node->keys + i) < key ) i++;
		
		//不存在,查找下一个
		if( i == node->size || *(node->keys + i) > key) 
			
		{	
			preNode = node;
			prePos = i;
			node = *(preNode->children + i);
		}
		else {
			break;
		}
	}
	
	remove(preNode, prePos, node, i);
	size--;
}

//删除node节点pos位置的关键字
void BTree::remove(BTreeNode* preNode, int prePos, BTreeNode* node, int pos){
	// cout<<"remove node "<<node<<" pos "<<pos<<endl;
	//移除之前如果长度不够需要先调整，否则会导致不合规
	if(node!=root && node->size == degree - 1) {
		int offset = ajust(preNode, prePos);
		//offset == -1这种情况节点node和前一个节点合并已经被删除。。
		if(offset == -1) {
			node = *(preNode->children + prePos - 1);
			pos += degree;
		}else{
			pos += offset;
		}
	}

	BTreeNode* left;
	BTreeNode* right;
	left = *(node->children + pos);
	right = *(node->children + pos + 1);
	if(node->isLeaf){
		//叶子结点直接删
		for(int i = pos; i < node->size; i++){
			*(node->keys + i) = *(node->keys + i + 1);
		}
		node->size--;
	}
	else if(left->size > degree - 1){
		//左侧最右边节点上移,再递归
		*(node->keys + pos) = *(left->keys + left->size - 1);
		remove(node, pos, left, left->size - 1);
	}
	else if(right->size > degree - 1){
		//右侧最左边节点上移，再递归
		*(node->keys + pos) = *(right->keys);
		remove(node, pos + 1, right, 0);
	}
	else{
		merge(node, pos);
		//合并后总长2*degree-1, key位于中间
		remove(node, pos, left, degree - 1);
	}
}



void BTree::print(){
	// count = 0;
	// printInOrder(root);
	// cout<<endl<<"记录数量"<<size<<",实际打印数量"<<count<<endl;
	count = 0;
	printByNode(root);
	cout<<endl<<"记录数量"<<size<<",实际打印数量"<<count<<endl;
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
	cout<<node<<" 深度:"<<depth<<", 数量:"<<node->size<<", keys:";
	for(int i = 0; i < node->size; i++){
		count++;
		cout<< *(node->keys + i) << " ";
	}
	
	if(!node->isLeaf){
		cout<<", children: ";
		for(int  i = 0; i < node->size + 1; i++){
			cout<< *(node->children + i) << " ";
		}
		cout<<endl;
		for(int  i = 0; i < node->size + 1; i++){
			printByNode(*(node->children + i));
		}
	}
	else{
		cout<<endl;
	}
	depth--;
}

void BTree::check(){
	cout<<"自由度"<<degree<<endl;
	cout<<"宽度上限"<<2*degree - 1<<endl;
	cout<<"宽度下限"<<degree - 1<<endl;
	count = 0;
	check(root);
	if(count == 0) cout<<"b树合规"<<endl;
}

void BTree::check(BTreeNode* node){
	depth++;
	if(node == nullptr) return;
	if(node->size > 2*degree - 1 || node->size < degree - 1){
		count++;
		cout<<"深度"<<depth<<",节点"<<node<<"不合法 尺寸"<<node->size<<":";
		for(int i = 0; i < node->size; i++)cout<< *(node->keys + i) << " ";	
		cout<<endl;
	}
	
	if(!node->isLeaf){
		for(int  i = 0; i < node->size + 1; i++){
			check(*(node->children + i));
		}
	}
	depth--;
}


int main(){
	BTree btree(3);
	
	for(int i = 0; i < 40; i++){
		btree.insert(i);
		//btree.print();
	}
	
	for(int i = 0; i < 40; i++){
		//btree.search(random(2000));
		btree.remove(random(40));
		//btree.print();
	}
	
	for(int i = 40; i < 80; i++){
		btree.insert(i);
		//btree.print();
	}
	btree.print();
	btree.check();
	return 1;
}
