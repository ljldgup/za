/************************************************************************
   File Name: lz78.cpp
   Author: ljl
   Mail: 
   Created Time: Sun Sep 12 21:20:39 2021
************************************************************************/

#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<map>
using namespace std;
#define random(x) (rand()%(x+1))


unordered_map<string, int> prefixMap;
vector<string> prefixVector;


int windowSize = 1024*16;
int maxPrefixLength = 32;
struct CompressUnit{
	int index;
	char nextChar;
};

vector<CompressUnit> compressOneRound(char *lookaheadBuffer, int lookaheadLength, int &compressedCount){
	int left = 0;
	vector<CompressUnit> result;
	compressedCount = 0;
	
//	cout<<"lookaheadBuffer "<<lookaheadLength<<" :";
//	for(int i = 0; i < lookaheadLength; i++) cout<<*(lookaheadBuffer + i);
//	cout<<endl; 
	
	while(left < lookaheadLength && left < windowSize){
		string prefix = "";

		int index = 0;
		int i = 0;
		for(i = 0; i + left < lookaheadLength && i < maxPrefixLength; i++){
			prefix += *(lookaheadBuffer + left + i);
			if(prefixMap.find(prefix) == prefixMap.end()) break;
			else index = prefixMap[prefix];
		}
		
        //预防匹配到最后一位 
		if(prefixMap.find(prefix) != prefixMap.end()){
			i--;
			prefix = prefix.substr(0,prefix.length() - 1);
			index = prefixMap[prefix];
//			cout<<"old "; 
		}else{
//			cout<<prefix<<" "<<prefixMap.size()<<endl<<endl;
			prefixMap[prefix] = prefixMap.size();
		}
		CompressUnit unit = {index, *(lookaheadBuffer + left + i)};
//		cout<<prefix<<" "<<unit.index<<" "<<unit.nextChar<<endl;
		result.push_back(unit);
		left += i + 1;
//		cout<<"left "<<left<<endl;
	}


	
	compressedCount = left;
//	cout<<endl<<"compressedCount"<<compressedCount<<endl;
	return result;
}

void compressFile(char *srcPath, char* targetPath){
	prefixMap.clear();
	prefixMap[""] = 0;
//	cout<<srcPath<<endl<<targetPath<<endl;
	FILE* src;
	FILE* target;
	if((src = fopen(srcPath,"rb"))==NULL){
        printf("source file cannot open \n");
		return;
	}
	if((target = fopen(targetPath,"wb"))==NULL){
        printf("target file cannot open \n");	
		return;
	}

	//三个窗口，1.搜索区 2-3压缩内容lookaheadBuffer，每次只压缩2窗口中开头的内容，
	//压缩完毕后，将2-3移到1-2窗口，读入新的内容到填充3窗口
	char *compressBuffer = new char[windowSize*2];
	
	//先读取一个窗口的内容，在循环中前移，循环内压缩必须要有2缓冲窗口以上，否则跳至结尾
	int compressedCount = 0;
	int lookaheadLength = 0;
	int unitCout = 0;
	int count = 0;
	int readLength;
	
	while(readLength = fread(compressBuffer + lookaheadLength - compressedCount, sizeof(char), 2*windowSize - (lookaheadLength - compressedCount), src)){
		lookaheadLength = lookaheadLength - compressedCount + readLength;
		vector<CompressUnit> &&result = compressOneRound(compressBuffer, lookaheadLength, compressedCount);
		for(auto &unit: result) fwrite((void*)&unit, sizeof(CompressUnit), 1, target);
//		cout<<"compressedCount"<<compressedCount<<endl<<endl<<endl;
		memcpy(compressBuffer, compressBuffer + compressedCount, lookaheadLength - compressedCount);
		count += readLength;
		unitCout += result.size();
//		//cout<<count<<endl;
	}
		
	lookaheadLength = lookaheadLength - compressedCount;
	if(unitCout == 0) lookaheadLength = count;	

	//仅剩下小于等于一个窗口的内容，使用最后一次读出的量
	vector<CompressUnit> &&result = compressOneRound(compressBuffer, lookaheadLength, compressedCount);
	for(auto &unit: result) fwrite((void*)&unit, sizeof(CompressUnit), 1, target);
	
	cout<<"压缩总字节 "<<count<<endl;

	if(prefixMap.size()<40){
//		cout<<endl<<"prefix map"<<endl;
		map<int, string> sortMap;
		for(auto [key, value]:prefixMap) sortMap[value] = key;
//		for(auto [key, value]:sortMap) cout<<key<<" "<<value<<endl;
	}
	fclose(src);
	fclose(target);	
	delete compressBuffer;
}

void deCompressFile(char *srcPath, char* targetPath){
	prefixVector.clear();
	prefixVector.push_back("");
	prefixMap.clear();
	prefixMap[""] = 0;
	
//	cout<<srcPath<<endl<<targetPath<<endl;
	FILE* src;
	FILE* target;
	//这里要用二进制，否则遇到0x1A 被任务CTRL+Z，会结束读取
	if((src = fopen(srcPath,"rb"))==NULL){
        printf("source file cannot open \n");
		return;
	}
	if((target = fopen(targetPath,"wb"))==NULL){
        printf("target file cannot open \n");	
		return;
	}

	CompressUnit unit;
	//最多需要一个窗口search，一个窗口匹配 + nextChar
	char *deCompressBuffer = new char[windowSize*2];
	int localOffset = 0;
	int count = 0;
	while(fread((void*)(&unit), sizeof(CompressUnit), 1, src)){
		string prefix = prefixVector[unit.index];
//		cout<<prefix<<" "<<unit.index<<" "<<unit.nextChar<<endl;
		
		prefix = prefix + unit.nextChar;
		if(localOffset + prefix.length() >= windowSize*2){
			fwrite((void*)deCompressBuffer, sizeof(char), localOffset, target);	
			localOffset = 0;
		}
		
		memcpy(deCompressBuffer + localOffset, prefix.c_str(), prefix.length());

		//有一部分由于长度限制最终没有找到新前缀，故没有插入新的前缀，这里需要判断
		if(prefixMap.find(prefix) == prefixMap.end()){
			prefixVector.push_back(prefix);
			prefixMap[prefix] = prefixVector.size();
		}
	
		localOffset += prefix.length();
		count += prefix.length();
	}
	 
	//最后一个字符有可能会多处理起来比较麻烦，可以考虑吧源文件大小写入到压缩文件里，后面直接截断
	fwrite((void*)deCompressBuffer,sizeof(char), localOffset, target);
	cout<<"解压总字节 "<<count<<endl;
	if(prefixMap.size()<40){
//		cout<<endl<<"prefix map"<<endl;
		map<int, string> sortMap;
		for(auto [key, value]:prefixMap)sortMap[value] = key;
//		for(auto [key, value]:sortMap) cout<<key<<" "<<value<<endl;
	}
	fclose(target);
	fclose(src);
	delete deCompressBuffer;
}

void testCompressFile(){
	compressFile("D:/BaiduNetdiskDownload/test.txt", "D:/BaiduNetdiskDownload/test.txt.en78");
	deCompressFile("D:/BaiduNetdiskDownload/test.txt.en78", "D:/BaiduNetdiskDownload/test.txt.de78");
}

int main(){
	testCompressFile();
//	cout<<prefixMap.size()<<endl;

	long long int size = 0;
	for(auto [key, value]:prefixMap){
		size += key.length();
	}
	
	//字典不限制，这里size基本就是文件的字节长度
	cout<<"字典字节数："<<size<<endl;
	return 0;
}
