/************************************************************************
    > File Name: test.cpp
    > Author: ljl
    > Mail: 
    > Created Time: 2021年03月10日 14:52:24
************************************************************************/

#include<stdio.h>
//两人生日相同超过50%概率所需人数
void two_same_birthday(){
	double pro = 1.0;
	for(int i = 365 ; i > 0; i--){
		pro *= i/365.0;
		if(pro < 0.5){
			printf("%d \n", 365-i + 1) ;
			break;
		}
	}
}

//指定生日有两人相同 概率>50%所需人数
void determined_two_same_birthday(){
	double pro = 0.0;
	int i;
	for( i = 1; pro < 0.5;i++ ){
		pro = (i-1)*i/(365.0*365);
	}
	printf("%d \n", i);
}
int main(){
	//two_same_birthday();
	determined_two_same_birthday();
}
