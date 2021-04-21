/************************************************************************
    > File Name: huffman.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月21日  8:57:08
************************************************************************/

#include <algorithm>
#include<unordered_map>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
#define random(x) (rand()%(x+1))

struct Node{
	public:
		char ch;
		int freq;
		char prefix;
		Node *left;
		Node *right;
		
		Node(int c, int f){
			this->ch = c;
			this->freq = f;
			this->right = nullptr;
			this->left = nullptr;
		}

		bool operator > (const Node& n) const{
			return this->freq > n.freq;
		}
		
		bool operator < (const Node& n) const{
			return this->freq < n.freq;
		}
};

void set_prefix(Node* node){
	//cout<<node->ch<<' '<<node->freq<<endl;
	if(node->left != nullptr){
		node->left->prefix = '0';
		set_prefix(node->left);
	}
	
	if(node->right != nullptr){
		node->right->prefix = '1';
		set_prefix(node->right);
	}
}

void tree_print_delete(Node *node, string prefix){
	//cout<<prefix;
	if(node != nullptr && node->prefix != '?'){
		prefix += node->prefix;
		cout<<node->ch<<", freq:"<<node->freq<<", prefix:"<<prefix<<endl;
	}
	 
	if(node != nullptr){
		tree_print_delete(node->left, prefix);
		tree_print_delete(node->right, prefix);
	}
	delete node;
}


int main(){
	string text = "fsdgsglsdgjoewnhosdjglsdjglsdjglsdg";
	// scanf("%s",text);
	unordered_map<char, int> charFreq;
	for(auto c:text){
		auto it = charFreq.find(c);
		if(it == charFreq.end()){
			charFreq.insert(pair<char,int>(c, 1));
		}else{
			it->second++;
		}
	}
	
	vector<Node*> nodeList;
	for(auto p: charFreq){
		// cout<<p.first<<':'<<p.second<<endl;
		nodeList.push_back(new Node(p.first, p.second));
	}
	// for(int size = nodeList.size(); size > 1; size--){
		// Node n1 = nodeList[size - 1];
		// cout<<n1.ch<<' '<<n1.freq<<endl; 
	// }
	
	
	cout<<"-------------"<<endl;
	auto cmp = [](Node*&n1,Node*&n2) -> bool{return n1->freq > n2->freq;};
	make_heap(nodeList.begin(), nodeList.end(), cmp);
	for(int size = nodeList.size(); size > 1; size--){
		Node* n1 = nodeList[0];
		//cout<<n1.ch<<':'<<n1.freq<<endl;
		//pop_heap将将堆顶(所给范围的最前面)元素移动到所给范围的最后，并且将新的最大值置于所给范围的最前面
		pop_heap(nodeList.begin(), nodeList.end(), cmp);
		nodeList.pop_back();
		
		Node* n2 = nodeList[0];
		pop_heap(nodeList.begin(), nodeList.end(), cmp);
		nodeList.pop_back();
		
		Node *n3 = new Node('?', n1->freq + n2->freq);
		n3->left = n1;
		n3->right = n2;
		cout<<n3->ch<<' '<<n3->freq<<' '<<n3->left->ch<<' '<<n3->left->freq<<' '<<n3->right->ch<<' '<<n3->right->freq<<endl;
		nodeList.push_back(n3);
		push_heap(nodeList.begin(), nodeList.end(), cmp);
		// for(auto n:nodeList){
			// cout<< n.ch << ' ';
		// }
		// cout<<endl;
	}
	
	Node* root = nodeList[0];
	cout<<root->ch<<' '<<root->freq<<endl;
	set_prefix(root);
	string prefix = "";
	tree_print_delete(root, prefix);
	return 1;
}
