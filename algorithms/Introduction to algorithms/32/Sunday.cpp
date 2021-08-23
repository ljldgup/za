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

 //移动后直接check尾部，尾部不匹配则直接
 //尾部匹配则将p 根据偏移表进行移动
 int sundayMatch(const string &s, const string &p, vector<int> &rst){

     int i,j,t,count;

    rst.clear();
     //偏移表，假定只有小写
     int shift[26];
	 for(int i = 0; i < 26; i++){
		 shift[i] = p.length();
	 }
	 //memset只能设成0，-1，因为memset是一个一个比特位设值得
	 //memset(shift, p.length(), sizeof(shift));  
	 //for(int i = 0; i < 26; i++) shift[i] = p.length();
	 // for(i = 0; i < 26; i++) cout<<shift[i]<<' ';
	 // cout<<endl;
	 //对于字符c，s中和p尾部对应的是c，此时将p向前移动shift[c]个位置
	 //相同字母选择移动最小的值,即移动到最靠近尾部的位置
     for(i = 0; i < p.length();i++) shift[p[i] - 'a'] = p.length() - i;
	 for(i = 0; i < 26; i++) cout<<shift[i]<<' ';
	 cout<<endl;
     i = j = count = 0;
     while(i < s.length()){
         
		 //注意这里匹配是从首部匹配，而移动是从尾部进行移动  
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
		 //s中对应p尾部+1的字符下标，这里Sunday的算法是根据尾部+1位置移动的，
		 //因为无论成功还是失败，当前这个p.length-1长度的s子串都无法再用，尾部+1位置必然下次会匹配到
		 t = i + (p.length() - j);
		 
		 //这行貌似是多余的应为下面已经判断过了，循环开始 i和j同步增加，这个值始终不变
		 //if(t >= s.length()) break;
		 
		 //根据尾部字符进行移动，使得s在t位置能和p对应
		 i = i - j + shift[s[t] - 'a'];
		 j = 0;
		 
		 if(i + p.length() >= s.length()) break;
         
     }
     return count;
 }
 
int main(){
	string p = "aaababaa";
	vector<int> ans;
	for(auto c:p) cout<<c<<" ";
	cout<<endl;

	string s="yaaababaacdaaabaaaababaaababaaaaabaaaababaaaaababx";
	int count = sundayMatch(s, p, ans);
	cout<<s<<endl;
	cout<<count<<endl;
	for(auto pos:ans) cout<<pos<<':'<<s.substr(pos, p.length())<<endl;
}
