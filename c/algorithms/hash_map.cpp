/************************************************************************
    > File Name: hash_map.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月 7日  9:48:20
************************************************************************/

#include<iostream>
#include<vector>
#include<array>
#include<tuple>
#include<ctime>
#include<string>
#include<cmath>
#include <algorithm>
using namespace std;
#define random(x) (rand()%(x+1))

array<int, 10> primes= {233,239,241,251,257,263,269,271,277,281};

class HashMap{
	private: 
		vector<vector<tuple<string, string>>> buckets;
		double a;
		int b,p,bucket_num;
	public:
		HashMap(int);
		void put(string key, string value);
		void remove(string key);
		string search(string key);
		int hash(string key);
		void print();
};

HashMap::HashMap(int num){
	p = 49999; 
	a = (sqrt(5.0) - 1)/2.0;
	b = 1 + random(p - 2);
	bucket_num = num;
	for(int i = 0; i < bucket_num; i++){
		vector<tuple<string, string>> entryList;
		buckets.push_back(entryList);
	}
}

int HashMap::hash(string key){
	unsigned int acc = 0;
	for(auto c:key){
		acc = acc*63689  + c;
	}
	//乘法取模
	cout<<int(acc*a)%bucket_num<<endl;
	return int(acc*a)%bucket_num;
}

void HashMap::put(string key, string value){
	int location = hash(key);
	cout<<buckets[location].size()<<endl;
	auto index=find_if(buckets[location].begin(), buckets[location].end(), [=](tuple<string,string> t)->bool{return get<0>(t) == key;});
	if(index==buckets[location].end()){
		buckets[location].insert(buckets[location].begin(), make_tuple(key, value));
	}else{
		cout<<key<<"已存在\n";
	}
	cout<<"put finished"<<endl;
	
}

string HashMap::search(string key){
	int location = hash(key);
	auto index=find_if(buckets[location].begin(), buckets[location].end(), [=](tuple<string,string> t)->bool{return get<0>(t) == key;});
	if(index==buckets[location].end()){
		cout<<key<<"不存在\n";
	}else{
		return get<0>(*index);
	}
		cout<<"search finished"<<endl;
}

void HashMap::remove(string key){
	int location = hash(key);
	auto index=find_if(buckets[location].begin(), buckets[location].end(), [=](tuple<string,string> t)->bool{return get<0>(t) == key;});
	if(index==buckets[location].end()){
		cout<<key<<"不存在\n";
	}else{      
		buckets[location].erase(index);
	}
			cout<<"remove finished"<<endl;
}

void HashMap::print(){
	for(int i = 0; i < buckets.size(); i++){
		cout<<i<<": ";
		auto list = buckets[i];
		for(auto tp:list){
			cout<<get<0>(tp)<<"->"<<get<1>(tp)<<',';
		}
		cout<<endl;
	}
}

int main(){
	int length = random(65);
	HashMap map(length);
	
	// vector<vector<int>> test(length);
	// for(int i = 0; i < length; i++){
		// cout<<test[i].size()<<endl;
	// }
	
	for(int i = 0; i < length; i++){
		map.put(to_string(i*10),to_string(i*100));
	}
	
	map.put("test","test");
	map.print();
}


