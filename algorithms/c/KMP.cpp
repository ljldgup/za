/************************************************************************
    > File Name: KMP.cpp
    > Author: ljl
    > Mail: 
    > Created Time: Mon Nov  4 14:37:08 2019
************************************************************************/

#include<iostream>
#include<vector>
#include"string.h"
using namespace std;
void generateNext(const string &p, vector<int> &next){
	
	int i, k;
	next[0] = -1;
	//next[i] = k 含义在于 前缀p[0,k-1]，与后缀 p[i-k, i-1] 相匹配
	//注意 p[i],p[k] 均没参与比较
	//添加next[p.length()],意义是p中最大的匹配前后缀，用于在多次查找时，一次匹配结束后转到新的位置
	//否则无法处理搜索结果相连的情况
	for(i = 1; i <= p.length(); i++){
		
		k = next[i - 1];
		//p[i-1]!=p[k]失败时，转向p[k]匹配失败的移动位置next[k]，寻找最长的可匹配位置
		while(k >= 0 && p[i - 1] != p[k]) k = next[k];
		next[i] = k + 1;
	}
}


int kmpMatch(const string &s, const string &p, vector<int> &next, vector<int> &rst){
	
	int i,j,count;
	i = j = count = 0;
	
	rst.clear();
	while(i < s.length()){
		
		//cout<<s.length()<<' '<<i<<' '<<j<<endl ;
		//cout<<i<<'<'<<s.length()<<'='<<(i<s.length())<<endl;
		//cout<<j<<'<'<<p.length()<<'='<<(j<p.length())<<endl;
		
		//s.length() 返回的是unsigned int 和负数比较时会发生错误（负数由于占位符而大于无符号型）,所以单独判断j == -1
		while(i < s.length() && (j < p.length() || j == -1)){
			if(j == -1 || s[i] == p[j]){
				i++,j++;
			}
			else{
				//注意这里如果不匹配移动的匹配字符串p的位置，当前s[i]不变，这和有限自动机是有区别的
				j = next[j];
			}
		}
		
		if(j == p.length()){
			rst.push_back(i - j);
			count++;
			//移到最大匹配
			
			j = next[p.length()];
		}
	}
	return count;
}



int main(){
	string p = "aaababaa";
	vector<int> next(p.length());
	vector<int> ans;
	
	generateNext(p, next);
	for(auto c:p) cout<<c<<" ";
	cout<<endl;
	for(auto pos:next) cout<<pos<<" ";
	cout<<endl;

	string s="aaababaaaaabaaaababaaababaaaaabaaaababaaaaabab";
	int count = kmpMatch(s, p, next, ans);
	cout<<s<<endl;
	cout<<count<<endl;
	for(auto pos:ans) cout<<pos<<':'<<s.substr(pos, p.length())<<endl;

}
