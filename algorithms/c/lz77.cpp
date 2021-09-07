/************************************************************************
   File Name: lz77.cpp
   Author: ljl
   Mail: 
   Created Time: Mon Sep  6 09:27:33 2021
************************************************************************/

#include<iostream>
#include<algorithm>
#include<ctime>
#include<cstring>
#include<vector>
using namespace std;
#define random(x) (rand()%(x+1))

unsigned int windowSize = 1024;
struct CompressUnit{
	int offset;
	int longestMatchLength;
	char nextChar;
};


CompressUnit getCommonLongestMatch(char *lookaheadBuffer, 
	unsigned int lookaheadBufferLength, unsigned int searchBufferLength){

	char *searchBuffer = lookaheadBuffer - searchBufferLength;

	cout<<"getCommonLongestMatch"<<endl;
	cout<<lookaheadBufferLength<<endl;
	for(int i = 0; i < lookaheadBufferLength; i++) cout<<*(lookaheadBuffer+i);
	cout<<endl;
	
	cout<<searchBufferLength<<endl;
	for(int i = 0; (searchBuffer + i) != lookaheadBuffer; i++) cout<<*(searchBuffer+i);
	cout<<endl;
	
	int longestMatchLength = 0;
	int offset = 0;
	int left = 0;

	while(left < searchBufferLength - longestMatchLength ){
		int i = 0;
		while(i < lookaheadBufferLength && left + i < windowSize 
			&& *(lookaheadBuffer + i) == *(searchBuffer + left + i)) i++;
		//cout<< *(lookaheadBuffer + left + i)<<" "<< *(searchBuffer + i)<<endl;
		//cout<<left<<" "<<i<<" "<<endl;
		if(i > longestMatchLength){
			longestMatchLength = i;
			offset = searchBufferLength - left;
		}
		left++;
	}

	CompressUnit unit;
	unit.offset = offset;
	unit.longestMatchLength = longestMatchLength;
	unit.nextChar = *(lookaheadBuffer + longestMatchLength);
	return unit;
}

//连续压缩一个windowSize的数据，searchBuffer 在lookaheadBuffer左侧
//读取文件压缩，每轮windowSize压缩一次，压缩完将原来的字节右边移动一个windowSize,读取下一个windows补充 
vector<CompressUnit> compressOneRound(char *lookaheadBuffer, unsigned int aheadLength, unsigned int searchLength){ 
		vector<CompressUnit> compressResult;

		unsigned int lookaheadBufferLength, searchBufferLength;
		int compressCount = 0;
		while(compressCount < windowSize){
			lookaheadBufferLength = min(windowSize, aheadLength);
			searchBufferLength = min(windowSize, searchLength);
			CompressUnit unit = getCommonLongestMatch(lookaheadBuffer, lookaheadBufferLength, searchBufferLength);
			compressResult.push_back(unit);
			//cout<<lookaheadBuffer<<endl;
			cout<<unit.longestMatchLength<<" "<<unit.offset<<" "<<unit.nextChar<<endl;
			lookaheadBuffer += unit.longestMatchLength + 1;
			searchLength += unit.longestMatchLength + 1;
			aheadLength -= unit.longestMatchLength + 1;
			compressCount += unit.longestMatchLength + 1;
		}
		return compressResult;
}


void deCompress(vector<CompressUnit> &result, char *buffer){
	char* previousBuffer;

	for(auto unit: result){
		previousBuffer = buffer - unit.offset;
		for(int i = 0; i < unit.longestMatchLength;i++){
			*buffer = *previousBuffer;
			buffer++;
			previousBuffer++;
		}
		*buffer = unit.nextChar;
		buffer++;
	}
}

void testGetCommonLongestMatch(){
	char lookaheadBuffer[]="adbfefadbdbddfa";
	cout<<"lookaheadBuffer:"<<lookaheadBuffer<<endl;
	windowSize = strlen(lookaheadBuffer)/2;
	CompressUnit unit = getCommonLongestMatch(lookaheadBuffer + strlen(lookaheadBuffer)/2,  strlen(lookaheadBuffer)/2, strlen(lookaheadBuffer)/2);
	cout<<endl<<"----"<<endl;
	cout<<unit.longestMatchLength<<" "<<unit.offset<<" "<<unit.nextChar<<endl;
	
	char *searchBuffer = lookaheadBuffer - strlen(lookaheadBuffer)/2;
	for(int i = 0, j = strlen(searchBuffer) - unit.offset; i < unit.longestMatchLength;i++)
		cout<<*(searchBuffer + i + j);
}

void testCompressOneRound(){
	char *lookaheadBuffer = "124235123542341234213412342541241254";
	windowSize = strlen(lookaheadBuffer); 
	vector<CompressUnit> &&result = compressOneRound(lookaheadBuffer, strlen(lookaheadBuffer), 0);
	for(auto unit: result){
		 cout<<unit.longestMatchLength<<" "<<unit.offset<<" "<<unit.nextChar<<endl;
	}

	char *deCompressedBuffer = new char[strlen(lookaheadBuffer)];
	deCompress(result, deCompressedBuffer);
	cout<<"origin: "<<lookaheadBuffer<<endl;
	cout<<"handled:"<<deCompressedBuffer<<endl;
	delete[] deCompressedBuffer;
}




int main(){
	//testGetCommonLongestMatch();
	testCompressOneRound();
	return 0;
}
