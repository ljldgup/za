/************************************************************************
    > File Name: all_shortest_path.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年05月 4日 17:29:07
************************************************************************/

#include<iostream>
#include<stack>
using namespace std;
#define random(x) (rand()%(x+1))

int MAX = 10000000;

//这里由于pathRecord 只是记录了经过节点k，所以需要递归打印
void print_path(int size, int *pathRecord, int steps, int x, int y){
   int preNode = *(pathRecord + steps*size*size + x * size + y);
   if(steps >= 0 && preNode != x) {
       print_path(size, pathRecord, steps - 1, x, preNode);
       cout<<preNode + 1<<" ";
       print_path(size, pathRecord, steps - 1, preNode, y);
   }
    
}

void extend_shortest_path(int *weights, int size, int *prePathWeight, int* curPathWeight, int *prePathRecord, int *curPathRecord){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            int minSum = *(prePathWeight + i*size + j);
            int minK = *(prePathRecord + i*size + j);
            //这里在numpy中可以prePathWeight[i] + np.transpose(prePathWeight)[j]，然后求最大值和最大索引
            for(int k = 0; k < size; k++){
                if(*(prePathWeight + i*size + k) + *(prePathWeight + k*size + j) < *(prePathWeight + i*size + j)){
                    minSum = *(prePathWeight + i*size + k) + *(prePathWeight + k*size + j);
                    minK = k;
                }
            }
            
            *(curPathWeight + i*size + j) = *(prePathWeight + i*size + minK) + *(prePathWeight + minK*size + j);
            *(curPathRecord + i*size + j) = minK; 
            
        }
    }
}

//第一节的普通算法，实际上单源最短路径bell ford算法的矩阵化
void show_all_shortest_path(int *weights, int size){
    int* pathRecord = new int[size*size*size];
    int* pathWeight = new int[size*size*size];
    
    //初始化，第一步
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            *(pathWeight + i*size + j) = *(weights + i*size + j);
            *(pathRecord + i*size + j) = i;
        }
    }
    
    // for(int k = 0; k < size; k++){
        // for(int i = 0; i < size; i++){
            // for(int j = 0; j < size; j++){
                // cout<<*(pathWeight + k*size*size + i*size + j)<<" ";
            // }
            // cout<<endl;
        // }
        // cout<<endl;
    // }
    
    //这里实际上可以直接迭代
    for(int i = 1; i < size; i++){
        extend_shortest_path(weights, size, pathWeight + (i - 1)*size*size, pathWeight + i*size*size, 
            pathRecord + (i - 1)*size*size,  pathRecord + i*size*size);
    }
    
    for(int k = 0; k < size; k++){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                cout<<*(pathWeight + k*size*size + i*size + j)<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < i; j++){
            cout<<i + 1<<" to "<<j + 1<<" : ";
            print_path(size, pathRecord, size - 1, i, j);
            cout<<endl;
        }
    }
    cout<<"---------------------"<<endl;
    
    delete pathRecord;
    delete pathWeight;
}

//这里不知道为什么引入stack就直接报错？？
//g++编译器不匹配
void floydWarshallPrintPath(int size, int *pathRecord, int x, int y){
    stack<int> nodes;
    int tNode;
    
    //找到y的前驱后用前驱代替y，知道y==x为止，注意这里输出的路径是反向的
    for(int steps = size + 1; steps > 0; steps--){  
        tNode = *(pathRecord + (steps - 1)*size*size + x*size + y);
        
        if(x != tNode){
           nodes.push(tNode);
           //cout<<tNode + 1<<" ";
           y = tNode;
        }else{
            break;
        } 
    }
    
    while(!nodes.empty()) {
        cout<<nodes.top() + 1<<" ";
        nodes.pop();
    }
    
    cout<<endl;
}

void floydWarshall(int *weights, int size){
    //这里的pathRecord记录的是i到j路径，j的前驱
    int* pathRecord = new int[(size+1)*size*size]();
    int* pathWeight = new int[(size+1)*size*size]();
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            *(pathWeight + i*size + j) = *(weights + i*size + j);
            if(i != j && *(weights + i*size + j) != MAX){
                *(pathRecord + i*size + j) = i;
            }else{
                *(pathRecord + i*size + j) = -1;
            }
        }
    }
    cout<<"??";
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            //cout<<*(pathWeight + k*size*size + i*size + j)<<" ";
            cout<<*(pathRecord+ i*size + j)<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    
    int dij, dik, dkj, preNode;
    for(int k = 1; k <= size; k++){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                dij = *(pathWeight + (k - 1)*size*size + i*size + j);
                dik = *(pathWeight + (k - 1)*size*size + i*size + k - 1);
                dkj = *(pathWeight + (k - 1)*size*size + (k - 1)*size + j);
                if( dij > dik + dkj ) {
                    *(pathWeight + k*size*size + i*size + j) = dik + dkj;
                    //如果dik + dkj更优，则保存的是dkj记录中的上一个元素
                    *(pathRecord + k*size*size + i*size + j) = *(pathRecord + (k - 1)*size*size + (k - 1)*size + j);
                }else{
                    *(pathWeight + k*size*size + i*size + j) = dij;
                    *(pathRecord + k*size*size + i*size + j) = *(pathRecord + (k - 1)*size*size + i*size + j);
                }
            }
        }
        
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                //cout<<*(pathWeight + k*size*size + i*size + j)<<" ";
                cout<<*(pathRecord + k*size*size + i*size + j)<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        
    }
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < i; j++){
            cout<<i + 1<<" to "<<j + 1<<" : ";
            floydWarshallPrintPath(size, pathRecord, i, j);
        }
    }
    cout<<"---------------------"<<endl;
    
    delete pathRecord;
    delete pathWeight;
}

int main(){
	int size = 5;
    
    //注意，对角线左上右下这条对角线为0， 即weight[i][i] = 0;
    int weights1[5*5] = {
        0, 3, 8, MAX, -4,
        MAX, 0, MAX, 1, 7,
        MAX, 4, 0, MAX, MAX,
        2, MAX, -5, 0, MAX,
        MAX, MAX, MAX, 6, 0
    };
    show_all_shortest_path(weights1, size);
    
    
    int weights2[5*5] = {
        0, 3, 8, MAX, -4,
        MAX, 0, MAX, 1, 7,
        MAX, 4, 0, MAX, MAX,
        2, MAX, -5, 0, MAX,
        MAX, MAX, MAX, 6, 0
    };
    floydWarshall(weights2, size);
}
