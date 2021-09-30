#include<iostream>
#include<queue>
#include<stack>

using namespace std;

int ENTER = 0;
int SEARCH_LEFT = 1;
int SEARCH_RIGHT = 2;
struct Node
{
	Node *left;
	Node *right;
	int value;
	Node(int value){
		this->value = value;
		left = nullptr;
		right = nullptr;
	}

	
	~Node(){
		if(left != nullptr) delete left;
		if(right != nullptr) delete right;
	}
};

template<typename T>
T popQueue(queue<T> &values){
	T value = values.front();
	values.pop();
	return value;
}

template<typename T>
T popStack(stack<T> &values){
	T value = values.top();
	values.pop();
	return value;
}

Node* buildTree(queue<int> &values){
	if(values.size() == 0) return nullptr;
	queue<Node*> nodes;

	Node* root = new Node(popQueue(values));
	nodes.push(root);
	
	while(!nodes.empty()){
		Node *node = popQueue(nodes);
		cout<<node->value<<endl;	
		if(!values.empty()) {
			node->left = new Node(popQueue(values));
			nodes.push(node->left);
		}

		if(!values.empty()){
			node->right = new Node(popQueue(values));
			nodes.push(node->right);
		}
	}

	return root;	
}

void printTree(Node *root){
	if(root == nullptr) return ;
	printTree(root->left);
	cout<<root->value<<" ";
	printTree(root->right);	
}

void reverseTree(Node *root){
	//递归入栈 是函数，入参，行数，这里函数已经定了，如后两个，行数用标志替代
	stack<Node*> nodes;
	stack<int> flags;
	Node *cur = root;
	int flag = ENTER;
	
	while(true){	
//		if(cur != nullptr){
//			cout<<cur->value<<" ";
//			cout<<flag<<endl;
//		}
		
		if(cur == nullptr){
			cur = popStack(nodes);
			flag = popStack(flags);
		}

		else if(flag == ENTER){
			nodes.push(cur);
			flags.push(SEARCH_LEFT);
			cur = cur->left;
			flag = ENTER;
		}
		else if(flag == SEARCH_LEFT){
			nodes.push(cur);
			flags.push(SEARCH_RIGHT);
			cur = cur->right;
			flag = ENTER;
		}else{
			Node *t = cur->left;
			cur->left = cur->right;
			cur->right = t;
			if(nodes.empty()) break;
			cur = popStack(nodes);
			flag = popStack(flags);
		}
	}
}


int main(){
	queue<int> list;
	int nums[] = {9,7,11,4,8,10,12,2};
	for(int i = 0;i < 8; i++) list.push(nums[i]);

	Node *root = buildTree(list);
	printTree(root);
	cout<<endl;
	reverseTree(root);
	printTree(root);
	cout<<endl;
	delete root;
	return 0;
}


