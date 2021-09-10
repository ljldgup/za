/*****   *******************************************************************
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
#include <unordered_map>
using namespace std;
#define random(x) (rand()%(x+1))

//窗口开大以后，压缩效果会好很多，但时间增长较大，可以考虑用map+滑窗优化
int windowSize = 8096;
struct CompressUnit{
	int offset;
	int longestMatchLength;
	char nextChar;
};

unordered_map<char, vector<int>> position_record;
int searchStartPostion = 0;

void updateMap(char *lookaheadBuffer, int searchBufferLength, CompressUnit &unit){
//	cout<<"updateMap"<<endl;
//	cout<<"move "<<unit.longestMatchLength + 1<<endl;
//	cout<<unit.nextChar<<" "<<unit.longestMatchLength<<" "<<unit.offset<<endl;
	char *oldSearchBufferStart = lookaheadBuffer - searchBufferLength;
	int deleteLength = min(searchBufferLength + unit.longestMatchLength + 1 - windowSize, searchBufferLength);
	for(int i = 0; i < deleteLength; i++){
		char key = *(oldSearchBufferStart + i);
//		cout<<"delete "<<key<<" at "<< *(position_record[key].begin())<<endl;
		position_record[key].erase(position_record[key].begin());	
	}
	
	for(int i = 0; i < unit.longestMatchLength + 1; i++){

		char key = *(lookaheadBuffer + i);
		if(position_record.find(key) == position_record.end()){
			position_record[key] = {};
		}
//		cout<<"add "<<key<<" at "<< searchStartPostion + searchBufferLength + i<<endl;
		position_record[key].push_back(searchStartPostion + searchBufferLength + i);
	}
	
	if(searchBufferLength + unit.longestMatchLength + 1 > windowSize) 
		searchStartPostion += unit.longestMatchLength + 1;
}

CompressUnit getCommonLongestMatch(char *lookaheadBuffer, 
	int lookaheadBufferLength, int searchBufferLength){
//	cout<<"getCommonLongestMatch"<<endl;

	char *searchBuffer = lookaheadBuffer - searchBufferLength;

//	cout<<"lookaheadBufferLength "<<lookaheadBufferLength<<endl;
//	cout<<"searchBufferLength    "<<searchBufferLength<<endl;
//	cout<<"lookaheadBuffer:"<<endl;
//	for(int i = 0; i < lookaheadBufferLength; i++) cout<<*(lookaheadBuffer+i);
//	cout<<endl;
	
	// cout<<"searchBuffer:"<<endl;
	// for(int i = 0; (searchBuffer + i) != lookaheadBuffer; i++) cout<<*(searchBuffer+i);
	// cout<<endl;
	
	int longestMatchLength = 0;
	int offset = 0;
	int left = 0;
	char startChar = *lookaheadBuffer;
	// cout<<"postition_map:"<<endl;
	// for(auto [key, positions]: position_record){
		// cout<<key<<":";
		// for(auto position:positions) cout<<position<<" ";
		// cout<<endl;
	// }
	// cout<<endl;
	
	if(position_record.find(startChar) != position_record.end() && position_record[startChar].size() > 0){
		for(auto left: position_record[startChar]){
			left = left - searchStartPostion;
//			cout<<startChar<<" left "<<left<<endl;
			int i = 0;
			while(i < lookaheadBufferLength && left + i < searchBufferLength 
				&& *(lookaheadBuffer + i) == *(searchBuffer + left + i)) i++;

			if(i > longestMatchLength){
				longestMatchLength = i;
				offset = searchBufferLength - left;
			}
//			cout<< *(lookaheadBuffer + left + i)<<" "<< *(searchBuffer + i)<<endl;
//			cout<<left<<" "<<i<<" "<<endl;
			left++;

		}
	}


	CompressUnit unit;
	unit.offset = offset;
	unit.longestMatchLength = longestMatchLength;
	unit.nextChar = *(lookaheadBuffer + longestMatchLength);
	
	return unit;
}


//连续压缩一个windowSize的数据，searchBuffer 在lookaheadBuffer左侧
//读取文件压缩，每轮windowSize压缩一次，压缩完将原来的字节右边移动一个windowSize,读取下一个windows补充 
vector<CompressUnit> compressOneRound(char *lookaheadBuffer, int aheadLength, int searchLength){ 
//		cout<<"compressOneRound"<<endl;
//		cout<<lookaheadBuffer<<" "<<aheadLength<<" "<<searchLength<<endl;
		vector<CompressUnit> compressResult;

		int lookaheadBufferLength, searchBufferLength;
		int compressedCount = 0;
		while(compressedCount < windowSize && aheadLength > 0){
			lookaheadBufferLength = min(windowSize, aheadLength);

			searchBufferLength = min(windowSize, searchLength);
			CompressUnit unit = getCommonLongestMatch(lookaheadBuffer, lookaheadBufferLength, searchBufferLength);
			compressResult.push_back(unit);
//			cout<<lookaheadBuffer<<endl;
//			cout<<unit.longestMatchLength<<" "<<unit.offset<<" "<<unit.nextChar<<endl;
			updateMap(lookaheadBuffer, searchBufferLength ,unit);
			lookaheadBuffer += unit.longestMatchLength + 1;
			searchLength += unit.longestMatchLength + 1;
			aheadLength -= unit.longestMatchLength + 1;
			compressedCount += unit.longestMatchLength + 1;
		}
		return compressResult;
//		cout<<"compressOneRound finished"<<endl;
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

void compressFile(char *srcPath, char* targetPath){
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
	char *compressBuffer = new char[windowSize*3];
	
	//先读取一个窗口的内容，在循环中前移，循环内压缩必须要有2缓冲窗口以上，否则跳至结尾
	int readLength  = fread(compressBuffer + windowSize, sizeof(char), windowSize, src);
	int previousReadLength = readLength;
	int count = readLength;
	int unitCount = 0;
	int searchLength = 0;
	int compressedCount = windowSize;
	int lookaheadLength = 0;
	
	while(readLength = fread(compressBuffer + windowSize * 3 - compressedCount, sizeof(char), compressedCount, src)){
		lookaheadLength = windowSize * 2 - compressedCount + readLength;
//		cout<<"searchPart ";
//		for(int i = windowSize - searchLength; i < windowSize; i++){
//			cout<<*(compressBuffer+i);
//		}
//		cout<<endl<<endl;
//		
//		cout<<"lookaheadPart ";
//		for(int i = windowSize; i < windowSize + lookaheadLength; i++){
//			cout<<*(compressBuffer+i);
//		}
//		cout<<endl<<endl;
		
		vector<CompressUnit> &&result = compressOneRound(compressBuffer + windowSize, lookaheadLength, searchLength);
		compressedCount = 0;
		for(auto &unit: result) {
			fwrite((void*)&unit, sizeof(CompressUnit), 1, target);
			compressedCount += unit.longestMatchLength + 1;
		}

//		cout<<"compressedCount "<<compressedCount<<endl;
		memcpy(compressBuffer, compressBuffer + compressedCount, windowSize * 3 - compressedCount);

		previousReadLength = readLength;
		count += readLength;
		unitCount += result.size();
		searchLength = windowSize;
//		cout<<count<<endl;
	}
	
	
	lookaheadLength = lookaheadLength - compressedCount;
//	cout<<"lookaheadLength"<<lookaheadLength<<endl;
//	cout<<"searchPart ";
//	for(int i = windowSize - searchLength; i < windowSize; i++){
//		cout<<*(compressBuffer+i);
//	}
//	cout<<endl<<endl;
	
//	cout<<"lookaheadPart ";
//	for(int i = windowSize; i < windowSize + lookaheadLength; i++){
//		cout<<*(compressBuffer+i);
//	}
//	cout<<endl<<endl;
	
	

	//仅剩下小于等于一个窗口的内容，使用最后一次读出的量
	vector<CompressUnit> &&result = compressOneRound(compressBuffer + windowSize, lookaheadLength, searchLength);
//	cout<<"总字节"<<count<<endl;
//	cout<<"压缩点"<<unitCount<<endl;
	
	count = 0;
	for(auto unit: result) {
		fwrite((void*)&unit, sizeof(CompressUnit), 1, target);
		count += unit.longestMatchLength + 1;
	}
	//最后一个为0的话需要减掉
//	cout<<"还原总长度"<<count<<endl;

	fclose(src);
	fclose(target);	
	delete compressBuffer;
}


void deCompressFile(char *srcPath, char* targetPath){
	searchStartPostion = 0;
	position_record.clear();
	
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

	CompressUnit *unit = new CompressUnit();
	//最多需要一个窗口search，一个窗口匹配 + nextChar
	char *deCompressBuffer = new char[windowSize*3];
	int localOffset = 0;
	int unitCount = 0;
	int count = 0;
	while(fread((void*)unit, sizeof(CompressUnit), 1, src)){
//		cout<<unit->nextChar<<" "<<unit->offset<<" "<<unit->longestMatchLength<<endl;

		if(localOffset + unit->longestMatchLength >= windowSize*3){
//			cout<<"write "<<windowSize<<" chars"<<endl;
			fwrite((void*)deCompressBuffer, sizeof(char), windowSize, target);
			memcpy(deCompressBuffer, deCompressBuffer + windowSize, localOffset - windowSize);
			localOffset -= windowSize;
		}
		if(unit->longestMatchLength > 0)
			memcpy(deCompressBuffer + localOffset, deCompressBuffer + localOffset - unit->offset, unit->longestMatchLength);
		
		*(deCompressBuffer + localOffset + unit->longestMatchLength) = unit->nextChar;
		
//		cout<<"deCompressResult ";
//		for(int i = localOffset; i < localOffset + unit->longestMatchLength + 1; i++) cout<<*(deCompressBuffer + i);
//		cout<<endl;
		
		localOffset += unit->longestMatchLength + 1;
		count += unit->longestMatchLength + 1;
		unitCount++;
	}

//	cout<<unitCount<<endl;
//	cout<<count<<endl;

//	cout<<"write "<<localOffset<<" chars"<<endl;
	//最后一个字符有可能会多处理起来比较麻烦，可以考虑吧源文件大小写入到压缩文件里，后面直接截断
	fwrite((void*)deCompressBuffer,sizeof(char), localOffset, target);
	fclose(target);
	fclose(src);
	delete deCompressBuffer;
	delete unit;
}

void testGetCommonLongestMatch(){
	char lookaheadBuffer[]="adbfefadbdbddfa";
//	cout<<"lookaheadBuffer:"<<lookaheadBuffer<<endl;
	windowSize = strlen(lookaheadBuffer)/2;
	CompressUnit unit = getCommonLongestMatch(lookaheadBuffer + strlen(lookaheadBuffer)/2,  strlen(lookaheadBuffer)/2, strlen(lookaheadBuffer)/2);
//	cout<<endl<<"----"<<endl;
//	cout<<unit.longestMatchLength<<" "<<unit.offset<<" "<<unit.nextChar<<endl;
	
	char *searchBuffer = lookaheadBuffer - strlen(lookaheadBuffer)/2;
//	for(int i = 0, j = strlen(searchBuffer) - unit.offset; i < unit.longestMatchLength;i++)
//		cout<<*(searchBuffer + i + j);
}

void testCompressAndDecompressOneRound(){
	char *lookaheadBuffer = "124235123542341234213412342541241254";
	windowSize = strlen(lookaheadBuffer); 
	vector<CompressUnit> &&result = compressOneRound(lookaheadBuffer, strlen(lookaheadBuffer), 0);
	for(auto unit: result){
//		 cout<<unit.longestMatchLength<<" "<<unit.offset<<" "<<unit.nextChar<<endl;
	}

	char *deCompressedBuffer = new char[strlen(lookaheadBuffer)];
	deCompress(result, deCompressedBuffer);
//	cout<<"origin: "<<lookaheadBuffer<<endl;
//	cout<<"handled:"<<deCompressedBuffer<<endl;
	delete[] deCompressedBuffer;
}


void testCompressFile(){
	compressFile("D:/BaiduNetdiskDownload/test.txt", "D:/BaiduNetdiskDownload/test.txt.lz77");
	deCompressFile("D:/BaiduNetdiskDownload/test.txt.lz77", "D:/BaiduNetdiskDownload/test.txt.de");
}

int main(){
	//testGetCommonLongestMatch();
	//testCompressOneRound();
	testCompressFile();
	return 0;
}
