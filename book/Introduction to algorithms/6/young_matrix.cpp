/************************************************************************
   File Name: young_matrix.cpp
   Author: ljl
   Mail: 
   Created Time: Tue Aug 24 00:12:34 2021
************************************************************************/

#include<iostream>
#include<algorithm>
#include<ctime>
using namespace std;
#define random(x) (rand()%(x+1))
const int WIDTH = 10;
const int HEIGHT = 12;
const int MAX = 100000;
const int MIN = -100000;
int matrix[WIDTH][HEIGHT];

//提取最小值到x,y
void minimizePosition(int x, int y){
	//cout<<x<<' '<<y<<endl;
	if(x == WIDTH-1 && y == HEIGHT-1) {
		return;
	}
	int cur,down,right;
	cur = matrix[x][y];
	
	if(y == HEIGHT - 1){
		down = MAX;
	}else{
		down =  matrix[x][y + 1];
	}
	
	if(x == WIDTH - 1){
		right = MAX;
	}else{
		right = matrix[x + 1][y];
	}
	
	if(cur > down && right >= down){
		matrix[x][y] = down;
		matrix[x][y + 1] = cur;
		minimizePosition(x,y + 1);
	}else if(cur > right && down >= right){
		matrix[x][y] = right;
		matrix[x + 1][y] = cur;
		minimizePosition(x + 1,y);
	}
}

void maximizePosition(int x, int y){
	if(x == 0 && y == 0) return;
	
	int up,left,cur;
	
	cur = matrix[x][y];
	
	if(x == 0)left = MIN;
	else left = matrix[x - 1][y];
	
	if(y == 0) up = MIN;
	else up = matrix[x][y - 1];

	if(cur < up && left <= up){
		matrix[x][y] = up;
		matrix[x][y - 1] = cur;
		maximizePosition(x, y - 1);
	}
	else if(cur < left && up <= left){
		matrix[x][y] = left;
		matrix[x - 1][y] = cur;
		maximizePosition(x - 1, y);
	}
}


int extract_min(){
	int minValue = matrix[0][0];
	matrix[0][0] = MAX;
	minimizePosition(0,0);
	return minValue;
}

void buildYoungMatrix(){
	//反复使用extract_min，每次保证右下方向已经是young举证,所有采用斜线，向左上平扫
	for(int i = WIDTH + HEIGHT - 2; i >= 0; i--){
		int m,n;
		if(i >= HEIGHT - 1){
			m = HEIGHT;
			n = i - n;
		}else{
			n = 0;
			m = i;
		}
		
		while(n < HEIGHT && m >= 0){
			minimizePosition(m,n);
			m--;
			n++;
		}
	}
}

void printMatrix(){
	cout<<endl;
	for(int i = 0; i < WIDTH;i++) cout<<"-";
	cout<<endl;
	
	for(int i = 0; i < WIDTH; i++){
		for(int j = 0; j < HEIGHT; j++){
			cout<<matrix[i][j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
}

void insertValue(int v){
	matrix[WIDTH - 1][HEIGHT - 1] = v;
	maximizePosition(WIDTH - 1, HEIGHT - 1);
}


int main(){
	srand(time(0));
	for(int i = 0; i < WIDTH; i++){
		for(int j = 0; j < HEIGHT; j++){
			matrix[i][j] = random(1000);
		}
	}

	printMatrix();
	buildYoungMatrix();

	for(int i = 0; i < WIDTH*WIDTH/2; i++) cout<<extract_min()<<" ";
	printMatrix();

	for(int i = 0; i < WIDTH*WIDTH/3; i++) insertValue(random(1000));
	printMatrix();
	return 0;
}
