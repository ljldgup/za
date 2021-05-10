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
int NUM = 128;
int P = 10007;

void rabinKrap(string s, string p){
	vector<int> hashValues;
	int sLen = s.length();
	int pLen = p.length();
	if(pLen > sLen)
		return;

	int tHashValue = 0;
	int times = 1;
	int pHashValue = 0;
	for(int i = 0; i< pLen;i++){
		tHashValue = (tHashValue*NUM + int(s[i]))%P;
		pHashValue = (pHashValue*NUM + int(p[i]))%P;
	}
	
	for(int i = 0; i< pLen - 1;i++){
		times *= NUM;
	}
	//这里可以取模，没有影响。。不取模会导致下面减掉的部分为负数
	times %= P;
	
	hashValues.push_back(tHashValue);
	for(int i = pLen; i< sLen; i++){
		tHashValue = tHashValue - times*int(s[i-pLen]);
		tHashValue = (tHashValue*NUM + s[i])%P;
		if(tHashValue < 0) tHashValue += P;
		hashValues.push_back(tHashValue);
	}
	
	for(auto v:hashValues)cout<<v<<' ';
	cout<<endl<<"---------------------"<<endl<<pHashValue<<' '<<times<<endl;

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

void finiteAutomata(string s, string p){
	unordered_map<char, vector<int>> transaction;
	for(auto c:s){
		if(transaction.find(c) == transaction.end()) 
			transaction[c] = vector<int>();
	}
	
	//todo build transaction
	for(int q = 0; q < p.length(); q++){
		
	}
	
	
	int status = 0;
	for(int i = 0; i < s.size(); i++){
		status = transaction[s[i]][status];
		if(status == p.size() - 1){
			cout<<i<<' '<<s.substr(i, p.length());
		}
	}
}

int main(){

	string s = "abcdefabcfegabcdeeabcdcde";
	string p = "abcd";
	rabinKrap(s, p);

	return 0;
}
