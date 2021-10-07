/************************************************************************
    > File Name: linked_list.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月 4日 22:34:59
************************************************************************/

#include<iostream>
#include<vector>
#include<ctime>
#include<unordered_map>
using namespace std;
#define random(x) (rand()%(x + 1))

class Node{
	public:
		Node *next;
		Node *prev;
		int value;
        long time;
		Node(int v){
			value = v;
		}
};

class LinkedList{
	private:
		int size;
		Node *nil;
	public:
		LinkedList(){
			nil = new Node(-10000000);
			nil->next = nil;
			nil->prev = nil;
			size = 0;
		}

		Node* search(int k){
			Node *head = nil->next;
			while(head->next != nil){
				if(head->value == k) return head;
				head = head->next;
			}
			return NULL;
		}

		//超限了就循环
		Node* get(int n){
			Node *head = nil->next;
			int i = 0;
			while(i < n){
				head = head -> next;
				i++;
			}
			return head;
		}
		
		void insert(int n, int v){
			cout<<"insert "<<v<<" postion "<<n<<endl;
			Node *node = get(n);
			cout<<node->value<<endl;
			insert(node, v);
		}
        
        Node *insertTail(int v){
			cout<<"insert "<<v<<" postion "<<size<<endl;
			Node *node = new Node(v);
            return insert(nil->next, v);
		}
        
        int removeTail(){
			Node *tail = nil->prev;
            if(tail != nil){
                int v = tail->value;
                cout<<"remove tail "<<v<<endl;
                remove(tail);
                return v;
            }
            return -1;
		}
		
		Node * insert(Node *pos, int v){
			Node *node = new Node(v);
			node->prev = pos->prev;
			node->next = pos;
			node->prev->next = node;
			pos->prev = node;
			size++;
            return node;
		}


		void remove(int n){
			cout<<"remove postion "<<n<<endl;
			Node *node = get(n);
			cout<<node->value<<endl;
			remove(node);
		}
		
		void remove(Node *cur){
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			size--;
            delete cur;
		}
        
        void update(Node *cur){
            cout<<"update :"<<cur->value<<endl;
            
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			
            Node *head = nil->next;
            nil->next = cur;
            cur->prev = nil;
            
            cur->next = head;
            head->prev = cur;
		}
		
		void print(){
			cout<<"size: "<<size<<endl;
			Node *head = nil->next;
			while(head!= nil){
				cout<<head->value<<' ';
				head = head->next;
			}
			cout<<endl;
		}
        
        int getSize(){
            return size;
        }
		
		~LinkedList(){
			Node *head = nil->next;
			Node *t;
			while(head != nil){
				t = head->next;
				delete head;
				head = t;
				//head = head->next;
			}
			delete nil;
		}
};

void LRUTest(){
    cout<<"test lru"<<endl;
    LinkedList linkedList;
    unordered_map<int, Node*> cache;
    for(int i = 0; i < 20; i++){
        int v = random(10);
        if(cache.find(v) == cache.end()){
            if(linkedList.getSize() >= 8){
                int oldValue = linkedList.removeTail();
                cache.erase(cache.find(oldValue));
            }
            Node* n = linkedList.insertTail(v);
            cache[v] = n;
        }
		else linkedList.update(cache[v]);
        linkedList.print();
	}
    
}

int main(){
	LinkedList linkedList;
	for(int i = 0; i < 20; i++){
		linkedList.print();
		linkedList.insert(random(i), random(100));
		linkedList.print();
		if(i%5==1){
			linkedList.remove(random(i));
		}
	}
    
    LRUTest();
}


