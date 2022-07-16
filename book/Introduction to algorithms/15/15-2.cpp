/************************************************************************
   File Name: 15-2.cpp
   Author: ljl
   Mail: 
   Created Time: Thu Oct  7 14:38:14 2021
************************************************************************/

#include<iostream>
#include<algorithm>
#include<ctime>
#include<vector>
#include<stack>
#include <tuple>
using namespace std;
#define random(x) (rand()%(x+1))
int M = 100;
int MAX = 1<<31;

int getCube(int num){
	cout<<"getCube "<<num<<endl;
	return num*num*num;
}

void printInOrder(vector<string> &words){
	//第i项代表0-i-1个单词的最优排列 
	vector<int> minCosts;
	
	// 第i项代表0-i-1个单词的最优排列 ， i-1前面一个单词位置，i-1则意味这前面没有 
	vector<int> previousPos;
	
	//无打印单词 
	minCosts.push_back(0);
	previousPos.push_back(-1); 

	unsigned int blankCount;
	int minCost, tCost, prePos;
	for(int n = 0; n < words.size(); n++){
		blankCount = M - words[n].length();
		minCost = getCube(blankCount);
		prePos = n;

		for(int i = n - 1; i >= 0; i--){
			//words[i].length() 是unsigned int 不能减号再比 
			if(blankCount < words[i].length() + 1) break;
			blankCount -= words[i].length() + 1;
			tCost = minCosts[i] + getCube(blankCount);
			
			if(tCost < minCost) {
				minCost = tCost;
				prePos = i;
			}
		}
		
		cout<<"cost:"<<n<<" "<<prePos<<" "<<minCost<<endl;; 
		minCosts.push_back(minCost);
		previousPos.push_back(prePos);
	}
	
	
	stack<tuple<int,int>> positions;
	int pos = words.size() - 1;
	while(pos >= 0){
		positions.push(make_tuple(pos, previousPos[pos]));
		pos = previousPos[pos] - 1;
	}

	for(auto pos:previousPos) cout<<pos<<" ";
	cout<<endl;
	
	while(!positions.empty()){
		auto [ed, st] = positions.top();
		positions.pop();
		for(int i = st; i <= ed; i++)cout<<words[i]<<" ";
		cout<<endl;
	}

}


int main(){
	vector<string> words = {"independence", "they", "were", "signing", "a", "promissory", "note", "to", "which", "every", "american", "was", "to", "fall", "heir", "this", "note", "was", "a", "promise", "that", "all", "men", "yes", "black", "men", "as", "well", "as", "white", "men", "would", "be", "guaranteed", "the", "unalienable", "rights", "of", "life", "liberty", "and", "the", "pursuit", "of", "happiness", "it", "is", "obvious", "today", "that", "america", "has", "defaulted", "on", "this", "promissory", "note", "insofar", "as", "her", "citizens", "of", "color", "are", "concerned", "instead", "of", "honoring", "this", "sacred", "obligation", "america", "has", "given", "the", "negro", "people", "a", "bad", "check", "a", "check", "which", "has", "come", "back", "marked", "insufficient", "funds"};
	printInOrder(words);
	return 0;
}
