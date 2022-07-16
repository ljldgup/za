/************************************************************************
    > File Name: longest_common_sequence.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年04月17日 23:21:00
	最长公共子串
************************************************************************/

#include<iostream>
#include<string>
#include<ctime>
#include<vector>
using namespace std;
#define random(x) (rand()%(x+1))

void LCS(string s1, string s2){
	int len1 = s1.length();
	int len2 = s2.length();
	if(len1 == 0 || len2 == 0 ) return; 

	vector<vector<string>> dp;
	for(int i = 0; i < len1 + 1; i++){
		vector<string> v(len2 + 1);
		v[0] = "";
		dp.push_back(v);	
	}

	for(int j = 0; j < len2; j++){
		dp[0][j] = "";
	}

	string t1;
	for(int i = 0; i< len1; i++){
		for(int j = 0; j < len2; j++){
			cout<<i<<' '<<j<<endl;
			cout<<s1[i]<<" "<<s2[j]<<endl;
			if(s1[i] == s2[j]){
				t1 = dp[i][j] + s1[i];
			}else{
				t1 = dp[i][j];
			}

			if(t1.length() > dp[i+1][j].length() 
					&& t1.length() > dp[i][j+1].length()){
				dp[i+1][j+1] = t1;
			}else if(dp[i+1][j].length() > dp[i][j+1].length()){
				dp[i+1][j+1] = dp[i+1][j];
			}else{
				dp[i+1][j+1] = dp[i][j+1];
			}
		}
	}
	cout<<"finished"<<endl;
	for(auto v:dp){
		for(auto s:v){
			cout<<s<<"\t";
		}
		cout<<endl;
	}
	cout<<dp[len1][len2]<<endl;
}


int main(){
	string s1,s2;
	cin>>s1>>s2;
	//cout<<s1<<endl<<s2<<endl;
	LCS(s1,s2);
}
