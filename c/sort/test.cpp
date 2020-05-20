/************************************************************************
    > File Name: test.cpp
    > Author: ljl
    > Mail: 
    > Created Time: Sat Nov  2 13:38:07 2019
************************************************************************/

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<random>
#include<time.h>
#include"test.h"
using namespace std;

#define random(x) (rand()%x)
#define SHOW_NUM 80
int main(){
    clock_t start,end;
    double endtime;
    srand((int)time(0));
    
    for(int len = 1; len < 100000; len *= 4){
        cout<<"长度 "<<len <<"---------------"<<endl;
        int *num1 = (int*)malloc(sizeof(int) * len);
        int *num2 = (int*)malloc(sizeof(int) * len);
        
        for(int i = 0; i < len; i++) *(num1 + i) = random((len*10));
        
        
        memcpy(num2, num1, sizeof(int) * len);
        start=clock();		//程序开始计时
        directInsertSort(num2, len);
        end=clock();	
        if(len < SHOW_NUM) {
            for(int i = 0; i < len; i++)  cout<< *(num2 + i) <<' ';
            cout<<endl;
        }
        else{         
            endtime = (double)(end-start)/CLOCKS_PER_SEC;
            cout<<"directInsertSort time:"<<endtime<<endl;		//s为单位
        }
        
        memcpy(num2, num1, sizeof(int) * len);
        start=clock();		//程序开始计时
        bubbleSort(num2, len);
        end=clock();	
        if(len < SHOW_NUM) {
            for(int i = 0; i < len; i++)  cout<< *(num2 + i) <<' ';
            cout<<endl;
        }
        else{         
            endtime = (double)(end-start)/CLOCKS_PER_SEC;
            cout<<"bubbleSort time:"<<endtime<<endl;		//s为单位
        }
        
        
        memcpy(num2, num1, sizeof(int) * len);
        start=clock();		//程序开始计时
        selectSort(num2, len);
        end=clock();	
        if(len < SHOW_NUM) {
            for(int i = 0; i < len; i++)  cout<< *(num2 + i) <<' ';
            cout<<endl;
        }
        else{         
            endtime = (double)(end-start)/CLOCKS_PER_SEC;
            cout<<"selectSort time:"<<endtime<<endl;		//s为单位
        }
        
        memcpy(num2, num1, sizeof(int) * len);
        start=clock();		//程序开始计时
        shellSort(num2, len);
        end=clock();	
        if(len < SHOW_NUM) {
            for(int i = 0; i < len; i++)  cout<< *(num2 + i) <<' ';
            cout<<endl;
        }
        else{         
            endtime = (double)(end-start)/CLOCKS_PER_SEC;
            cout<<"shellSort time:"<<endtime<<endl;		//s为单位
        }
        
        memcpy(num2, num1, sizeof(int) * len);
        start=clock();		//程序开始计时
        mergeSort(num2, len);
        end=clock();	
        if(len < SHOW_NUM) {
            for(int i = 0; i < len; i++)  cout<< *(num2 + i) <<' ';
            cout<<endl;
        }
        else{         
            endtime = (double)(end-start)/CLOCKS_PER_SEC;
            cout<<"mergeSort time:"<<endtime<<endl;		//s为单位
        }
        
        memcpy(num2, num1, sizeof(int) * len);
        start=clock();		//程序开始计时
        quickSort(num2, len);
        end=clock();	
        if(len < SHOW_NUM) {
            for(int i = 0; i < len; i++)  cout<< *(num2 + i) <<' ';
            cout<<endl;
        }
        else{         
            endtime = (double)(end-start)/CLOCKS_PER_SEC;
            cout<<"quickSort time:"<<endtime<<endl;		//s为单位
        }
        
        memcpy(num2, num1, sizeof(int) * len);
        start = clock();		//程序开始计时
        countSort(num2, len);
        end=clock();	
        if(len < SHOW_NUM) {
            for(int i = 0; i < len; i++)  cout<< *(num2 + i) <<' ';
            cout<<endl;
        }
        else{         
            endtime = (double)(end-start)/CLOCKS_PER_SEC;
            cout<<"countSort time:"<<endtime<<endl;		//s为单位
        }
        
        memcpy(num2, num1, sizeof(int) * len);
        start = clock();		//程序开始计时
        radixSort(num2, len);
        end=clock();	
        if(len < SHOW_NUM) {
            for(int i = 0; i < len; i++)  cout<< *(num2 + i) <<' ';
            cout<<endl;
        }
        else{         
            endtime = (double)(end-start)/CLOCKS_PER_SEC;
            cout<<"radixSort time:"<<endtime<<endl;		//s为单位
        }
        
        memcpy(num2, num1, sizeof(int) * len);
        start = clock();		//程序开始计时
        heapSort(num2, len);
        end=clock();	
        if(len < SHOW_NUM) {
            for(int i = 0; i < len; i++)  cout<< *(num2 + i) <<' ';
            cout<<endl;
        }
        else{         
            endtime = (double)(end-start)/CLOCKS_PER_SEC;
            cout<<"heapSort time:"<<endtime<<endl;		//s为单位
        }
        
        free(num1);
        free(num2);
    }
}
