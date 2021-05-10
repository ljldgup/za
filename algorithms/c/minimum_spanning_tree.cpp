/************************************************************************
   File Name: minimum_spanning_tree.cpp
   Author: ljl
   Mail: 
   Created Time: 2021年04月27日  9:38:27
************************************************************************/

#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<tuple>
#include<set>
using namespace std;
#define random(x) (rand()%(x+1))
int MAX = 10000000;

//key 用于prim 选取， pi上一个点
struct Node{
	char name;
	int key;
	char pi;
	Node(char n, int k){
		name = n;
		key = k;
		pi = ' '; 
	}
};


struct Edge{
	Node* fromNode;
	Node* toNode;
	int weight;
	Edge(Node* f, Node* t, int w){
		fromNode = f;
		toNode = t;
		weight = w;
	}
};

void print(unordered_map<char, Node*> vertexMap, unordered_map<char, vector<Edge*>*> graph){	
	for(auto Edge:graph){
		cout<<"Edge:"<<Edge.first<<" ";
		for(auto e:*Edge.second){
			cout<<e->fromNode->name<<' '<<e->toNode->name<<' '<<e->toNode->key<<' '<<e->weight<<" ";
		}
		cout<<endl;
	}
}

//查找点所在set
set<Node*>* findSet(set<set<Node*>*> vertexSet, Node* node){
	for(auto s:vertexSet){
		if( s->find(node)!= s->end()) return s;
	}
	return nullptr;
}

void kruskal(unordered_map<char, Node*> vertexMap, 
			unordered_map<char, vector<Edge*>*> graph){	 
			
	int sum = 0;
	set<set<Node*>*> resultSet;
	for(auto n:vertexMap){
		resultSet.insert(new set<Node*>{n.second});
	}
	
	vector<Edge*> EdgeList;
	for(auto v:graph){
		for(auto e:*v.second){
			EdgeList.push_back(e);
		}
	}
	
	auto comparator = [](Edge* e1, Edge* e2)->bool{return e1->weight < e2->weight;};
	
	sort(EdgeList.begin(), EdgeList.end(), comparator);
	
	set<Node*> *s1, *s2;
	for(auto e: EdgeList){
		s1 = findSet(resultSet, e->fromNode);
		s2 = findSet(resultSet, e->toNode);

		//节点两侧处于不同回路中，不会形成环
		if(s1 != nullptr && s2 != nullptr && s1 != s2){
			cout<<e->fromNode->name<<" "<<e->toNode->name<<" "<<e->weight<<endl;
			sum += e->weight;
			set_union(s1->begin(), s1->end(), s2->begin(), s2->end(), inserter(*s1, s1->begin()));
			resultSet.erase(s2);
		}
	}
	

	for(auto s: resultSet){
		for(auto n: *s){
			cout<<n->name<<" "; 
		}
		cout<<endl;
	}
	cout<<"sum"<<sum<<endl;
}

void prim(unordered_map<char, Node*> vertexMap, 
			unordered_map<char, vector<Edge*>*> graph){	  
	cout<<"prim"<<endl;
	int sum = 0;
	vector<Node*> minHeap;
	set<Node*> usedSet;
	set<Node*> resultSet;
	Node* minKeyNode;
	auto comparator = [](Node* n1, Node* n2)->bool{return n1->key > n2->key;};
	
	int length = vertexMap.size();
	
	for(auto n:vertexMap){
		minHeap.push_back(n.second);
	}
	vertexMap['a']->key = 0;
	make_heap(minHeap.begin(), minHeap.begin() + length, comparator);
	
	while(length > 0){
		// for(auto n: minHeap){
			// cout<<n->name<<' '<<n->key<<' ';
		// }
		// cout<<endl;
		
		minKeyNode = minHeap[0];
		resultSet.insert(minKeyNode);
		sum += minKeyNode->key;
		cout<<minKeyNode->name<<" "<<minKeyNode->key<<endl;
		
		pop_heap(minHeap.begin(), minHeap.begin() + length, comparator);
		length--;
		
		for(auto e:*graph[minKeyNode->name]){
			if(e->weight < e->toNode->key){
				e->toNode->key = e->weight;
				e->toNode->pi = minKeyNode->name;
			}
		}
		make_heap(minHeap.begin(), minHeap.begin() + length, comparator);
		

		
	}
	cout<<"sum:"<<sum<<endl;
}




int main(){
	unordered_map<char, Node*> vertexMap;
	unordered_map<char, vector<Edge*>*> graph;
	
	vector<tuple<char, char, int>> data{
		{'a', 'b', 4},
		{'a', 'h', 8},
		{'b', 'h', 11},
		{'b', 'c', 8},
		{'h', 'i', 7},
		{'h', 'g', 1},
		{'i', 'g', 6},
		{'i', 'c', 2},
		{'c', 'f', 4},
		{'g', 'f', 2},
		{'c', 'd', 7},
		{'d', 'f', 14},
		{'d', 'e', 9},
		{'f', 'e', 10}
	};
	
	for(char c:{'a','b','c','d','e','f','g','h', 'i'}){
		vertexMap[c] = new Node(c, MAX);
		graph[c]  = new vector<Edge*>();
	}
	
	for(auto d:data){
		Edge* e = new Edge(vertexMap[get<0>(d)], vertexMap[get<1>(d)], get<2>(d));
		graph[get<0>(d)]->push_back(e);
		e = new Edge(vertexMap[get<1>(d)], vertexMap[get<0>(d)], get<2>(d));
		graph[get<1>(d)]->push_back(e);
	}

	kruskal(vertexMap, graph);
	//prim(vertexMap, graph);
	
	for(auto Edge:graph){
		for(auto e:*Edge.second){
			delete e;
		}
		delete graph[Edge.first];
		delete vertexMap[Edge.first];
	}
	
	return 0;
}
