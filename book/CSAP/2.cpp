#  include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef unsigned char *byte_pointer;

//typedef unsigned int size_t;
void show_bytes(byte_pointer array, size_t length){
	size_t i = 0;
	for(i=0;i<length;i++) printf(" %.2x ", array[i]);
	printf("\n");
} 


void show_int(int x){
	show_bytes((byte_pointer)&x, sizeof(int));
}


void show_float(float x){
	show_bytes((byte_pointer)&x, sizeof(float));
}

void show_long(long x){
	show_bytes((byte_pointer)&x, sizeof(long));
}

// pointer 指针
void show_pointer(void* x){
	show_bytes((byte_pointer)&x, sizeof(void*));
}

void test_show_byte(int val){
	int ival = val;
	float fval = (float)ival; 
	long lval = (long)ival;
	int *pval = &ival;
    
    // 使用64位后寻址变成了8个字节，但是long还是4个字节
	show_int(ival);
	show_float(fval);
	show_long(fval);
	show_pointer(pval);
} 

void test_limit(){
	int x = 2147483647;
	int y = 2147483647/2;
	int upOverFlow = x + y;
	
    //群，交换律
	printf("%d + %d = %d\n", x,y, upOverFlow);
	printf("%d - %d = %d\n", upOverFlow ,x, upOverFlow - x);
	printf("~%d = %d \n", x, ~x);
	printf("~%d = %d \n", y, ~y);
	printf("~%d = %d \n", x+1, ~(x+1));
	
}


int main(int argc, char** argv) {
	printf("%d", sizeof(long)); 
	test_show_byte(12345);
	test_limit();
	return 0;
}
