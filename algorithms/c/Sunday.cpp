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

 //移动后直接check尾部，尾部不匹配则直接，从尾部后一个开始匹配
 //尾部匹配则将p 根据偏移表进行移动
 int sundayMatch(const string &s, const string &p, vector<int> &rst){

     int i,j,t,count;

    rst.clear();
     //偏移表，假定只有小写
     int shift[26]={p.length()};
	 cout<< shift[0] << endl;
     for(i = 0; i < p.length();i++) shift[p[i] - 'a'] = p.length() - i;
	 for(i = 0; i < 26; i++) cout<<shift[i]<<' ';
	 cout<<endl;
     i = j = count = 0;
     while(i < s.length()){
         
         while(i < s.length() && j < p.length()){
             if(s[i] == p[j]){
                 i++,j++;
             }
             else break;
         }

         if(j == p.length()){
             rst.push_back(i - j);
             count++;
         }
		 
		 //移动s,无论是否匹配
		 //s中当前尾部字符下标
		 t = i + (p.length() - j);
		 if(t >= s.length()) break;
		 i = i - j + shift[s[t] - 'a'];
		 j = 0;
		 if(i + p.size() >= s.size()) break;
         
     }
     return count;
 }
 
int main(){
	string p = "aaababaa";
	vector<int> ans;
	for(auto c:p) cout<<c<<" ";
	cout<<endl;

	string s="aaababaaaaabaaaababaaababaaaaabaaaababaaaaabab";
	int count = sundayMatch(s, p, ans);
	cout<<s<<endl;
	cout<<count<<endl;
	for(auto pos:ans) cout<<pos<<':'<<s.substr(pos, p.length())<<endl;
}
