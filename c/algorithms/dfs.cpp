/************************************************************************
    > File Name: dfs.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月25日 23:39:23
************************************************************************/

#include<iostream>
#include<unordered_map>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;
#define random(x) (rand()%(x+1))



int time = 0;
list<char> order; 

struct Node{
	char color;
	char name;
	int d;
	int f;

	Node(char c){
		name = c;
	};
};


void dfs_visit(unordered_map<char, vector<char>*> &graph, unordered_map<char, Node*> vertex, char v){
	time += 1;
	vertex.at(v)->d = time;
	vertex.at(v)->color = 'g';
	
	for(auto v1:*graph.at(v)){
		if(vertex.at(v1)->color == 'w'){
			cout<<v1<<' ';
			dfs_visit(graph, vertex, v1);
		}
	}

	vertex.at(v)->color = 'b';
	time += 1;
	vertex.at(v)->f = time;
	order.push_front(v);
}

void dfs(unordered_map<char, vector<char>*> &graph, unordered_map<char, Node*> vertex){
	for(auto v:vertex){
		v.second->color = 'w';
	}
	time = 0;
	for(auto v:vertex){
		if(v.second->color == 'w'){
			cout<<"begin with "<<v.first<<" :";
			dfs_visit(graph, vertex, v.first);
			cout<<"fininsed"<<endl;
		}
	}
}

void generateTranposeGraph(unordered_map<char, vector<char>*> &graph, unordered_map<char, vector<char>*> &graphT){
	for(auto p:graph) graphT[p.first] = new vector<char>{};
	
	for(auto p:graph){

		for(auto v:*p.second){
			graphT[v]->push_back(p.first);
		}
	}
}

void scc(unordered_map<char, vector<char>*> &graph, unordered_map<char, Node*> vertex, list<char> order){

	for(auto v:vertex){
		v.second->color = 'w';
	}
	time = 0;

	for(auto c:order){
		if(vertex.at(c)->color == 'w'){
			cout<<"begin with "<<c<<" ";
			dfs_visit(graph, vertex, c);
			cout<<"fininsed"<<endl;
		}
	}
}

int main(){
	unordered_map<char,vector<char>*> graph;
	unordered_map<char,vector<char>*> graphT;
	unordered_map<char, Node*> vertex;
	
	graph['a'] = new vector<char>{'b'};
	graph['b'] = new vector<char>{'e', 'f', 'c'};
	graph['c'] = new vector<char>{'d', 'g'};
	graph['d'] = new vector<char>{'c', 'h'};
	graph['e'] = new vector<char>{'a', 'f'};
	graph['f'] = new vector<char>{'g'};
	graph['g'] = new vector<char>{'f', 'h'};
	graph['h'] = new vector<char>{'h'};


	for(auto p:graph){
		vertex[p.first] = new Node(p.first);
		cout<<p.first<<":";
		for(auto e:*p.second){
			cout<<e<<' ';
		}
		cout<<endl;
	}

	//注意这里第一个节点就搜索完了,并不是一条路走完，而是回溯，继续走完的
	dfs(graph, vertex);
	for(auto v: vertex){
		Node *n = v.second;
		cout<<n->name<<' '<<n->color<<' '<<n->d<<' '<<n->f<<endl;
	}

	//拓扑排序
	cout<<"toplogic_order ";
	for(auto c:order){
		cout<<c<<" ";
	}
	cout<<endl;

	// reverse(order.begin(), order.end());
	// for(auto p:graph){
		// reverse(p.second->begin(), p.second->end());
	// }

	generateTranposeGraph(graph, graphT);

	cout<<"领接链表转置"<<endl;
	for(auto p:graphT){
		cout<<p.first<<":";
		for(auto e:*p.second){
			cout<<e<<' ';
		}
		cout<<endl;
	}

	cout<<"强联通分量"<<endl;
	scc(graphT, vertex, order);

	for(auto p:graphT){
		delete p.second;
	}
	
	for(auto p:graph){
		delete p.second;
	}

	for(auto n:vertex){
		delete n.second;
	}
	return 1;
}
