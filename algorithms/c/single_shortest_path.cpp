/************************************************************************
   File Name: single_shortest_path.cpp
   Author: ljl
   Mail: 
   Created Time: 2021年04月28日 19:52:55
************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
#include<tuple>
#include<unordered_map>
using namespace std;
#define random(x) (rand()%(x+1))
int MAX = 10000000;
int time = 0;

struct Node{
	char pi;
	char name;
	char color;
	int d;
	int f;
	Node(char n){
		name = n;
	}
};

struct Edge{
	Node* from;
	Node* to;
	int weight;
	Edge(Node* n1, Node* n2, int w){
		from = n1;
		to = n2;
		weight = w;
	}
};

void initialize_single_source(unordered_map<Node*, vector<Edge*>*> graph, Node* s){
	
	for(auto [n, e]: graph){
		n->d = MAX;
		n->pi = '?';
		n->color = 'w';
	}
	s->d = 0;
	time = 0;
}

void relax(Edge* edge){
	
	Node* u = edge->from;
	Node* v = edge->to;
	int w = edge->weight;
	//cout<<edge<<endl;
	//cout<<v<<" "<<v<<" "<<w<<endl;
	//cout<<"relax "<<v->name<<" "<<v->d<<" "<< u->name<<" "<<u->d<<" "<<w<<endl;

	if(v->d > u->d + w){
		// cout<<"relax "<<v->name<<" "<<v->d<<" "<< u->name<<" "<<u->d<<" "<<w<<endl;
		v->d = u->d + w;
		v->pi = u->name;
	}
}

void print_path(unordered_map<char, Node*> vertex, Node* v){
	cout<<"逆向路径:";
	while(v->pi != '?'){
		cout<<v->name<<" ";
		v = vertex[v->pi];
	}
	cout<<v->name<<endl;
}

bool bellmanFord(unordered_map<Node*, vector<Edge*>*> graph, Node* s){
				
	initialize_single_source(graph, s);
	for(int i = 0; i < graph.size(); i++){
		//cout<<i<<endl;
		for(auto graphPair: graph){
			for(auto edge: *graphPair.second){
				relax(edge);
			}
		}
		// for(auto [n, e]: graph) {
			// cout<<n->name<<" "<<n->d<<" "<<n->pi<<endl;
		// }
		// cout<<"-------------------------"<<endl;
	}
	
	for(auto graphPair: graph){
		for(auto edge: *graphPair.second){
			//cout<<edge->to<<" "<<edge->from<<" "<<edge->weight<<endl;
			if(edge->to->d > edge->from->d + edge->weight){
				return false;
			}
		}
	}
	
	return true;
}

bool dfs_visit(unordered_map<Node*, vector<Edge*>*> graph, Node* s){
	time++;
	s->d = time;
	s->color = 'g';
	for(auto edge: *graph[s]){
		if(edge->to->color == 'g') return false;
		
		if(edge->to->color == 'w') {
			//有环
			if(!dfs_visit(graph, edge->to)) return false;
		}
		

	}
	time++;
	s->f = time;
	s->color = 'b';
	
	return true;
}

bool get_by_dfs(unordered_map<Node*, vector<Edge*>*> graph, Node* s){
	initialize_single_source(graph, s);
	for(auto [n, edges]: graph){
		if(n->color == 'w') {
			if(!dfs_visit(graph, n)) return false;
		}
	}

	vector<Node*> nodeList;
	for(auto [n, edges]:graph){
		nodeList.push_back(n);
	}

	sort(nodeList.begin(), nodeList.end(), [](Node* n1, Node* n2)->bool{return n1->f > n2->f;});
	
	initialize_single_source(graph, s);
	for(auto n: nodeList){
		for(auto e:*graph[n]){
			relax(e);
		}
	}
	
	return true;
}

bool dijkstra(unordered_map<Node*, vector<Edge*>*> graph, Node* s){
	vector<Node*> nodes;
	int length = graph.size();
	for(auto[n, edges]:graph){
		nodes.push_back(n);
	}
	
	initialize_single_source(graph, s);
	
	auto cmp = [](Node* n1, Node* n2)->bool{return n1->d > n2->d;};
	make_heap(nodes.begin(), nodes.begin() + length, cmp);
	for(int i = 0; i < graph.size(); i++){
		Node* n = nodes[0];
		cout<<n->name<<endl;
		for(auto [n, e]: graph) {
			cout<<n->name<<" "<<n->d<<" "<<n->pi<<endl;
		}
		cout<<"-------------------------"<<endl;
		
		pop_heap(nodes.begin(), nodes.begin() + length, cmp);
		length--;
		
		for(auto edges: *graph[n]){
			if(edges->weight < 0){
				return false;
			}
			relax(edges);
		}
		make_heap(nodes.begin(), nodes.begin() + length, cmp);
		

	}
	return true;
}


int main(){
	char name;
	Node* node;
	Edge* edge;
	
	//bellmanFord数据,普适方法
	vector<tuple<char, char, int>> graphData1 {
		{'s', 't', 6},
		{'s', 'y', 7},
		{'t', 'y', 8},
		{'t', 'x', 5},
		{'t', 'z', -4},
		{'y', 'z', 9},
		{'y', 'x', -3},
		{'x', 't', -2},
		{'z', 'x', 7},
		{'z', 's', 2}
	};

	
	//有向无环，dfs数据
	vector<tuple<char, char, int>> graphData2 {
		{'s', 't', 2},
		{'s', 'x', 6},
		{'t', 'x', 7},
		{'t', 'y', 4},
		{'t', 'z', 2},
		{'x', 'y', -1},
		{'x', 'z', 1},
		{'y', 'z', -2}
	};
	
	//dijkstra,不能有负数，允许有环
	vector<tuple<char, char, int>> graphData3 {
		{'s', 't', 10},
		{'s', 'y', 5},
		{'t', 'y', 2},
		{'t', 'x', 1},
		{'y', 't', 3},
		{'y', 'z', 2},
		{'y', 'x', 9},
		{'x', 'z', 4},
		{'z', 'x', 6},
		{'z', 's', 7}
	};
	
	unordered_map<Node*, vector<Edge*>*> graph;
	unordered_map<char, Node*> vertex;
	for(auto c:{'s', 't', 'x', 'y', 'z'}){
		vertex[c] = new Node(c);
		//这里每个都需要加，不然initialize_single_source无法都初始化到
		graph[vertex[c]] = new vector<Edge*>();
	}

	for(auto [fromName, toName, weight]:graphData3){
		Node* from = vertex[fromName];
		Node* to = vertex[toName];
		graph[from]->push_back(new Edge(from, to, weight));
	}

	//不存在的索引会返回0，同时将值设定为0
	//cout<<"不存在的索引（返回0）："<<vertex['?']<<endl;
	//if(vertex['?']){}

	if(!dijkstra(graph, vertex['s'])){
	// if(!get_by_dfs(graph, vertex['s'])){
	// if(!bellmanFord(graph, vertex['s'])){
		cout<<"有权重负值的环路"<<endl;	
	}else{
		print_path(vertex, vertex['z']);
	}
	
	

	//释放
	for(auto [name, edgeList]: graph){
		for(auto e: *edgeList){
			//cout<<e->from->name<<" "<<e->to->name<<" "<<e->weight<<endl;
			delete e;
		}
		delete edgeList;
	}
	
	for(auto [name, node]: vertex) {
		if(node){
			// cout<<name<<" "<<node->d<<" "<<node->pi<<endl;
			delete node;
		}
	}
	return 1;
}
