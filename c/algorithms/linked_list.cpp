/************************************************************************
    > File Name: linked_list.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月 4日 22:34:59
************************************************************************/

#include<iostream>
#include<vector>
#include<ctime>
using namespace std;
#define random(x) (rand()%(x))

class Node{
	public:
		Node *next;
		Node *prev;
		int value;
		Node(int v){
			value = v;
		}
};

class LinkedList{
	private:
		int length;
		Node *nil;
	public:
		LinkedList(){
			nil = new Node(-10000000);
			nil->next = nil;
			nil->prev = nil;
			length = 0;
		}

		Node* search(int k){
			Node *head = nil->next;
			while(head->next != nil){
				if(head->value == k) return head;
				head = head->next;
			}
			return NULL;
		}
		
		void insert(int n, int v){
			Node *head = nil->next;
			insert(head, v);
		}
		
		void insert(Node *pos, int v){
			Node *node = new Node(v);
			pos->prev->next = node;
			pos->next->prev = node;
			node->prev = pos->prev;
			node->next = pos;
			length++;
		}

		void remove(Node *pos){
			pos->prev->next = pos->next;
			pos->next->prev = pos->prev;
			length--;
		}
		
		void print(){
			cout<<length<<endl;
			Node *head = nil->next;
			while(head!= nil){
				cout<<head->value<<' ';
				head = head->next;
			}
			cout<<endl;
		}
		
		~LinkedList(){
			Node *head = nil->next;
			Node *t;
			while(head != nil){
				t = head->next;
				delete head;
				head = t;
				head = head->next;
			}
			delete nil;
		}
};

int main(){
	LinkedList linkedList;
	for(int i = 0; i < 20; i++){
		linkedList.insert(i, random(100));
	}
	linkedList.print();
}


