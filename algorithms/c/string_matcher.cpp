/************************************************************************
   File Name: string_matcher.cpp
   Author: ljl
   Mail: 
   Created Time: 2021年05月10日 16:38:09
************************************************************************/

#include<iostream>
#include<cstring>
#include<vector>
#include<unordered_map>
using namespace std;
#define random(x) (rand()%(x+1))
//这里用128有可能会导致times最终为0
int NUM = 127;
int P = 10007;

void rabinKrap(string s, string p){
	vector<int> hashValues;
	int sLen = s.length();
	int pLen = p.length();
	if(pLen > sLen)
		return;

	int tHashValue = 0;
	int times = 1;
	cout<<times<<endl;
	int pHashValue = 0;
	for(int i = 0; i< pLen;i++){
		tHashValue = (tHashValue*NUM + int(s[i]))%P;
		pHashValue = (pHashValue*NUM + int(p[i]))%P;
	}
	
	//注意每次乘完都取mod， 不然溢出成为负数的时候会出问题
	//提前算好取模的n次方
	for(int i = 0; i< pLen - 1;i++){
		times = (times * NUM)%P;
	}
	
	cout<<times<<endl;
	//这里可以取模，没有影响。。不取模会导致下面减掉的部分为负数
	
	hashValues.push_back(tHashValue);
	for(int i = pLen; i< sLen; i++){
		//减掉最左侧字符影响直接取模即可
		tHashValue = tHashValue - times*int(s[i-pLen])%P;
		//这里外层必须在mod一次，不然会超限
		tHashValue = ((tHashValue*NUM)%P + (s[i])%P)%P;
		if(tHashValue < 0) tHashValue += P;
		hashValues.push_back(tHashValue);
	}
	
	for(auto v:hashValues)cout<<v<<' ';
	cout<<endl<<"---------------------"<<endl<<s<<"哈希值"<<pHashValue<<" 倍数"<<times<<endl;

	bool flag;
	for(int i = 0; i < hashValues.size(); i++){
		if(hashValues[i] == pHashValue){
			flag = true;
			for(int j = i; j < i + pLen; j++){
				if(s[j] != p[j - i]){
					flag = false;
					break;
				}
			}
			if(flag) cout<<i<<':'<<s.substr(i, pLen)<<endl;
		}
	}
}

bool isPostfix(string x, string y){
	if( x.length() > y.length()) return false;
	if(x.length() == 0) return true;
	
	for(int i = 1; i <= x.length(); i++){
		if(x[x.length() - i] != y[y.length() - i]) return false;
	}
	
	return true;
}

void finiteAutomata(string s, string p){
	unordered_map<char, vector<int>> transaction;
	int k;
	for(auto c:s){
		if(transaction.find(c) == transaction.end()) 
			transaction[c] = vector<int>();
	}
	
	//todo build transaction
	//注意这里
	for(int q = 0; q < p.length() + 1; q++){
		for(auto [c, v]: transaction){
			k = q + 1 <= p.length() ? q + 1 : p.length();
			while(k >= 0){
				//k==0 的时候必然是后缀
				if(isPostfix(p.substr(0,k), p.substr(0,q) + c)){
					break;
				}
				k--;
			}
			transaction[c].push_back(k);
		}
	}
	
	cout<<"状态转移表"<<endl;
	for(auto [c, v]: transaction){
		cout<<c<<' ';
		for(auto q: v){
			cout<<q<<' ';
		}
		cout<<endl;
	}
	
	int status = 0;

	for(int i = 0; i < s.length(); i++){
		//cout<<transaction[s[i]][status];
		status = transaction[s[i]][status];
		if(status == p.size()){
			cout<<i - p.length() + 1<<' '<<s.substr(i - p.length() + 1, p.length())<<endl;
		}
	}
	//cout<<endl<<s<<endl;
}

int main(){

	string s = "abcdabcdabefcdabcdabfegabcdcdefeeabcdabcdabcde";
	string p = "abcdab";
	rabinKrap(s, p);
	finiteAutomata(s,p);
	return 0;
}
