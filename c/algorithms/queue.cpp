/************************************************************************
    > File Name: queue.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月 4日 21:40:40
************************************************************************/

#include<iostream>
#include<vector>
#include<ctime>
#include<limits>
using namespace std;
#define random(x) (rand()%(x))

class Queue{
	private:
		int *array;
		int tail,head,length;

	public:
		Queue(int len){
			length = len;
			array = new int[length];
			tail = head = 0;
		}

		void enqueue(int v){
			cout<<"enqueue "<<v<<endl;
			int new_tail = move_forward(tail);
			
			if(new_tail == head){
				cout<<"queue full"<<endl;
				return;
			}

			array[tail] = v;
			tail = new_tail;
		}

		int dequeue(){
			cout<<"dequeue ";
			if(head == tail){
				cout<<"empty"<<endl;
				return numeric_limits<int>::max();
			}
			int old_head = head;
			head = move_forward(head);
			cout<<array[old_head]<<endl;
			return array[old_head];
		}

		bool empty(){
			return head==tail;
		}

		int move_forward(int p){
			if(p == length - 1) return 0;
			return p + 1;
		}

		int move_backward(int p){
			if(p == 0) return length - 1;
			return p - 1;
		}

		void print(){
			if(empty()) return;
			
			cout<<"head:"<<head<<",tail:"<<tail<<"  ";
			if(head < tail){
				for(int i = head; i < tail; i++){
					cout<< array[i]<<' ';
				}
			}else{
				for(int i = head; i < length; i++){
					cout<<array[i]<<' ';
				}
				for(int i = 0; i < tail; i++){
					cout<<array[i]<<' ';
				}
			}
			cout<<endl;
		}

		~Queue(){
			delete array;
		}

};

int main(){
	//srand(time())
	Queue queue(10);
	int t;
	for(int i=0; i < 100; i++){
		t = random(100) % 3;
		if(t == 0){
			queue.print();
		} else if(t == 1){
			queue.dequeue();
		}else{
			queue.enqueue(i);
		}

	}
}
