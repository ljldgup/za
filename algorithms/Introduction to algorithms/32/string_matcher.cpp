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

vector<int> rabinKrap(string s, string p){
	vector<int> hashValues;
	int sLen = s.length();
	int pLen = p.length();
	if(pLen > sLen)
		return {};

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
	cout<<endl<<"---------------------"<<endl<<s<<endl;
	cout<<"哈希值"<<pHashValue<<" 倍数"<<times<<endl;

	bool flag;
	vector<int> rst;
	for(int i = 0; i < hashValues.size(); i++){
		if(hashValues[i] == pHashValue){
			flag = true;
			for(int j = i; j < i + pLen; j++){
				if(s[j] != p[j - i]){
					flag = false;
					break;
				}
			}
			if(flag) rst.push_back(i);
		}
	}
	return rst;
}

bool isPostfix(string x, string y){
	if( x.length() > y.length()) return false;
	if(x.length() == 0) return true;
	
	for(int i = 1; i <= x.length(); i++){
		if(x[x.length() - i] != y[y.length() - i]) return false;
	}
	
	return true;
}

vector<int> getPostfixOffsetList(string &p){
		vector<int> offsets = {1};
		for(int i = 0; i < p.length(); i++){
			int offset = offsets[offsets.size() - 1];
			while( i - offset >= 0 && p[i - offset] != p[i]) 
				offset += offsets[i - offset];
			offsets.push_back(offset);
		}
		cout<<"偏移量表"<<endl; 
		for(auto o:offsets)cout<<o<<" ";
		cout<<endl;
		
		//这里第i个位置的意义是当0-i-1匹配，i不匹配时，p向右移动的偏移量。 
		return offsets;
}



unordered_map<char, vector<int>> buildTransactionMap(string &s, string &p){
	unordered_map<char, vector<int>> transaction;
	vector<int>  &&offsetList= getPostfixOffsetList(p);
	int k;
	for(auto c:s){
		if(transaction.find(c) == transaction.end()) 
			//这里这个写法和{}应该是等价的，因为{}出了当前的
			transaction[c] = vector<int>();
	}
	
	//todo build transaction
	//注意这里
	for(int i = 0; i < p.length() + 1; i++){

		cout<<i<<endl;
		for(auto& [c, v]: transaction){
			
			// 这里处理了所有输入的可能性，
			// 而不是像kmp只有不匹配的时候根据上一个字符进行移动。
			//k = i + 1 <= p.length() ? i + 1 : p.length();
			//while(k >= 0){
			//	// k==0 的时候必然是后缀
				//string matchPart = p.substr(0,i) + c;
				//if(isPostfix(p.substr(0,k), matchPart)){
					//break;
				//}
				//k--;
			//}
			
			//使用kmp的前缀偏移数组来进行加速
			int pos = i;
			// 结尾字符不匹配，或者已经匹配完毕就移动 
			cout<<i<<endl;
			
			while(pos >= 0 && (pos == p.length() || c != p[pos])) pos -= offsetList[pos];
			 
			v.push_back(pos + 1);
		}
	}
	
	//状态转移表c字符的类别第i项代表0-i-1匹配下，输入c进入的新位置状态 
	cout<<"状态转移表"<<endl;
	for(auto [c, v]: transaction){
		cout<<c<<':';
		for(auto i: v){
			cout<<i<<',';
		}
		cout<<endl;
	}
	return transaction; 
}

vector<int> finiteAutomata(string &s, string &p){
	vector<int> rst;
	unordered_map<char, vector<int>> &&transaction = buildTransactionMap(s, p);

	int status = 0;
	for(int i = 0; i < s.length(); i++){
		//cout<<transaction[s[i]][status];
		//这里status就是p的位置
		status = transaction[s[i]][status];
		if(status == p.length()) rst.push_back(i - p.length() + 1);
	}
	//cout<<endl<<s<<endl;
	return rst;
}

int main(){

	string s = "abcdabcdabefcdabcdabfegabcdcdefeeabcdabcdabcde";
	string p = "abcdab";
	auto rst1 = rabinKrap(s, p);
	for(auto i: rst1){
			cout<<i<<' '<<s.substr(i, p.length())<<endl;
	}
	auto &&rst2 = finiteAutomata(s,p);
	for(auto i: rst2){
			cout<<i<<' '<<s.substr(i, p.length())<<endl;
	}
	return 0;
}
