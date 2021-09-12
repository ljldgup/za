/*****   *******************************************************************
   File Name: lz77.cpp
   Author: ljl
   Mail: 
   Created Time: Mon Sep  6 09:27:33 2021
************************************************************************/

#include<iostream>
#include<algorithm>
#include<list>
#include<cstring>
#include<vector>
#include <unordered_map>
using namespace std;
#define random(x) (rand()%(x+1))

//窗口开大以后，压缩效果会好很多，但时间增长较大，可以考虑用map+滑窗优化
int windowSize = 1024*16;
struct CompressUnit{
	int offset;
	int longestMatchLength;
	char nextChar;
};

//单独用map记录位置优化效果很一般，并且windowSize 大于第一轮文本长度时，
unordered_map<int, vector<int>> positionRecord;
int mapHashLength = 2;
int searchStartPostion = 0;

//采用链表记录没hashLength的hash值
list<int> hashList;
int listHashLength = 3;
int p = 996109;
int q = 1181;
int qp = 1;



int getHashValue(char* buffer, int length){
	int hashValue = 0;
	int i = 0; 
	for(; i < length; i++){
		 hashValue = (hashValue * q + (int)*(buffer + i))%p;
	}
	return hashValue;
}


CompressUnit getCommonLongestMatch(char *lookaheadBuffer, 
	int lookaheadBufferLength, int searchBufferLength){
	CompressUnit unit{0,0,*lookaheadBuffer};
	char *searchBuffer = lookaheadBuffer - searchBufferLength;

//	cout<<"searchBuffer:"<<endl;
//	for(int i = 0; (searchBuffer + i) != lookaheadBuffer; i++) cout<<*(searchBuffer+i);
//	cout<<endl;
	
	int longestMatchLength = 0;
	int offset = 0;
	int left = 0;

	while(left < searchBufferLength - longestMatchLength ){
		int i = 0;
		while(i < lookaheadBufferLength && left + i < searchBufferLength 
			&& *(lookaheadBuffer + i) == *(searchBuffer + left + i)) i++;

		if(i > unit.longestMatchLength){
			unit.offset = searchBufferLength - left;
			unit.longestMatchLength = i;
			unit.nextChar = *(lookaheadBuffer + unit.longestMatchLength);
		}
		left++;
	}
	return unit;
}

//这里将两个字符直接转成int存到map，而不是嵌套map
void updateMap(char *lookaheadBuffer, int searchBufferLength, CompressUnit &unit){
//	cout<<"updateMap"<<endl;
//	cout<<"move "<<unit.longestMatchLength + 1<<endl;
//	cout<<unit.nextChar<<" "<<unit.longestMatchLength<<" "<<unit.offset<<endl;
	char *searchBuffer = lookaheadBuffer - searchBufferLength;
	int deleteLength = searchBufferLength + unit.longestMatchLength + 1 - windowSize;
	for(int i = 0; i < deleteLength; i++){
		int key = getHashValue(searchBuffer + i, mapHashLength);
//		cout<<"delete "<<key<<" at "<< *(positionRecord[key].begin())<<endl;
		positionRecord[key].erase(positionRecord[key].begin());	
	}
	
	for(int i = 0; i < unit.longestMatchLength + 1; i++){
		if(i + 1 + searchBufferLength < 2) continue;
		
		int key = getHashValue(lookaheadBuffer +  i - 1, mapHashLength);
		if(positionRecord.find(key) == positionRecord.end()){
			positionRecord[key] = {};
		}
//		cout<<"add "<<key<<" at "<< searchStartPostion + searchBufferLength + i - 1<<endl;
		positionRecord[key].push_back(searchStartPostion + searchBufferLength + i - 1);
	}
	
	
	if(searchBufferLength + unit.longestMatchLength + 1 > windowSize) 
		searchStartPostion += searchBufferLength + unit.longestMatchLength + 1 - windowSize;
	
	// int size = 0; 
	// cout<<"postition_map:"<<endl;
	// for(auto [key, positions]: positionRecord){
		// cout<<key<<":";
		// for(auto position:positions) cout<<position<<"  ";
		// cout<<endl;
		// size += positions.size();
	// }
	
	// cout<<"searchStartPostion "<<searchStartPostion<<endl;
//	cout<<"map size "<<size<<endl;
//	cout<<"list size:"<<hashList.size()<<" "<<endl;
//	cout<<"updateMap ended"<<endl<<endl<<endl;
}


unordered_map<int, double> increaseFactorMap;
unordered_map<int, int> longestMatchLengthMap;


//根据已经处理的数据量，来设置窗口增大的提升因子
//随着匹配进行，逐渐减小最大匹配长度增长量，来提前结束匹配
double increaseFactor = 1;
void setIncreaseFactor(double unitCount){
	increaseFactor =  40.0/unitCount + 0.6;
}


bool matchLengthEnough(int key, int matchLength){
	if(longestMatchLengthMap.find(key) == longestMatchLengthMap.end()){
		longestMatchLengthMap[key] = matchLength;
		return false;
	}

	int expectLength = longestMatchLengthMap[key] * increaseFactor;
	if(expectLength > matchLength) return false;
	else if(expectLength < matchLength){
		longestMatchLengthMap[key] = matchLength;
	}
	return true;
}

CompressUnit getCommonLongestMatchWithMap(char *lookaheadBuffer, 
	int lookaheadBufferLength, int searchBufferLength){
//	cout<<"getCommonLongestMatch"<<endl;
	CompressUnit unit{0,0,*lookaheadBuffer};
	if(lookaheadBufferLength < mapHashLength) return unit;
	
	char *searchBuffer = lookaheadBuffer - searchBufferLength;

	// cout<<"searchBuffer:"<<endl;
	// for(int i = 0; (searchBuffer + i) != lookaheadBuffer; i++) cout<<*(searchBuffer+i);
	// cout<<endl;
		
	int longestMatchLength = 0;
	int offset = 0;
	int left = 0;
	int key = getHashValue(lookaheadBuffer, mapHashLength);
	
	if(positionRecord.find(key) != positionRecord.end() && positionRecord[key].size() > 0){
		for(auto left: positionRecord[key]){
			left = left - searchStartPostion;
//			cout<<startChar<<" left "<<left<<endl;
			
			//先从最长的地方开始比对，效果反而更差，因为有些是中间或者开始的地方不一样，并不能带来提升
			//int i = longestMatchLength - 1;
			//while(i >= 0 && left + i < searchBufferLength && *(lookaheadBuffer + i) == *(searchBuffer + left + i)) i--;
			//if(i >= 0) continue;

			int i = 0;
			while(i < lookaheadBufferLength && left + i < searchBufferLength 
				&& *(lookaheadBuffer + i) == *(searchBuffer + left + i)) i++;

			if(i > unit.longestMatchLength){
				unit.offset = searchBufferLength - left;
				unit.longestMatchLength = i;
				unit.nextChar = *(lookaheadBuffer + unit.longestMatchLength);
				if(matchLengthEnough(key, unit.longestMatchLength)) break;
			}
			
		}
	}

	updateMap(lookaheadBuffer, searchBufferLength ,unit);
	return unit;
}


void updateList(char *lookaheadBuffer, int searchBufferLength, CompressUnit &unit){
 
 	//cout<<"updateMap"<<endl;
	//if(searchBufferLength + unit.longestMatchLength + 1 < listHashLength) return;
		
	char currentChar;
	int length; 
	char lastFirstChar,firstChar;
	int hashValue;
	for(int i = 0; i < unit.longestMatchLength + 1; i++){

		currentChar = *(lookaheadBuffer + i);
		length = searchBufferLength + i + 1; 
		if(length > listHashLength){
			lastFirstChar = *(lookaheadBuffer - listHashLength + i);
			firstChar = *(lookaheadBuffer - listHashLength + i + 1);
			int lastHashVule = hashList.back();
			lastHashVule -= lastFirstChar*qp%p;
			if(lastHashVule < 0) lastHashVule += p; 
			hashValue = (lastHashVule*q%p + (int)currentChar)%p;
			hashList.push_back(hashValue);
		}
		
		//第一个 
		else if(length == listHashLength){
			firstChar = *(lookaheadBuffer - searchBufferLength);
			hashValue = getHashValue(lookaheadBuffer - searchBufferLength, listHashLength);
			hashList.push_back(hashValue);
		}
		

	}
	
	
	char *searchBuffer = lookaheadBuffer - searchBufferLength;
	int deleteLength = searchBufferLength + unit.longestMatchLength + 1 - windowSize;
	for(int i = 0; i < deleteLength; i++) hashList.pop_front();

	// for(auto v:hashList) cout<<v<<" ";
	// cout<<endl;
	// cout<<"list size:"<<hashList.size()<<" "<<endl;
//	cout<<"updateMap ended"<<endl<<endl<<endl;
}


CompressUnit getCommonLongestMatchWithList(char *lookaheadBuffer, 
	int lookaheadBufferLength, int searchBufferLength){
//	cout<<"getCommonLongestMatch"<<endl;

	CompressUnit unit{0,0,*lookaheadBuffer};
	if(lookaheadBufferLength < listHashLength) return unit;
	
	char *searchBuffer = lookaheadBuffer - searchBufferLength;

	//cout<<"searchBuffer "<<searchBufferLength<<":"<<endl;
	//for(int i = 0; (searchBuffer + i) != lookaheadBuffer; i++) cout<<*(searchBuffer+i);
	//cout<<endl;	
	int hashValue = getHashValue(lookaheadBuffer, listHashLength);
	//cout<<"hashValue "<<hashValue<<endl;
	char startChar = *lookaheadBuffer;
	int position = 0;
	for(auto hValue:hashList){
		//cout<<hValue<<" ";
		

		if(hValue != hashValue) {
			position++;
			continue;
		}
		
		int left = position;
		int i = 0;
		while(i < lookaheadBufferLength && left + i < searchBufferLength 
			&& *(lookaheadBuffer + i) == *(searchBuffer + left + i)) i++;

		if(i > unit.longestMatchLength){
			unit.offset = searchBufferLength - left;
			unit.longestMatchLength = i;
			unit.nextChar = *(lookaheadBuffer + unit.longestMatchLength);
		}
		position ++;
	}
	
	updateList(lookaheadBuffer, searchBufferLength ,unit);
//	cout<<"getCommonLongestMatch ended"<<endl<<endl<<endl;		
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
			//map速度相对快一点点，效果和正常的一样，
			//list使用网上说的hash比对但是，反而速度最慢，压缩效果也不好。。
			CompressUnit unit = getCommonLongestMatchWithMap(lookaheadBuffer, lookaheadBufferLength, searchBufferLength);
//			CompressUnit unit = getCommonLongestMatchWithList(lookaheadBuffer, lookaheadBufferLength, searchBufferLength);
//			CompressUnit unit = getCommonLongestMatch(lookaheadBuffer, lookaheadBufferLength, searchBufferLength);
			compressResult.push_back(unit);
//			cout<<lookaheadBuffer<<endl;
			//cout<<unit.longestMatchLength<<" "<<unit.offset<<" "<<unit.nextChar<<endl;
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
	positionRecord.clear();
	hashList.clear();
	
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

//		setIncreaseFactor(unitCount);
//		cout<<count<<endl;
	}
		
	lookaheadLength = lookaheadLength - compressedCount;
	if(searchLength == 0) lookaheadLength = count;
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
	cout<<"总字节"<<count<<endl;
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
	positionRecord.clear();
	
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
	for(int i = 0; i < listHashLength - 1;i++){
		qp *= q;
		qp %= p;
	}
	//testGetCommonLongestMatch();
	//testCompressOneRound();
	testCompressFile();
	return 0;
}
