#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x) (rand()%x)
int count = 0;
void matrix_print(int *matrix, int length){
	for(int i = 0; i < length; i++){
		for(int j = 0; j < length; j++){
			printf("%d\t", *(matrix + i*length + j));
		}
		printf("\n");
	}
	//count++;
	//printf("%d-----------------------------\n", count);
}


void matrix_add(int *matrix1, int *matrix2,int *matrix3,  int length){
	for(int i = 0; i < length; i++){
		for(int j = 0; j < length; j++){
			*(matrix3 + i*length + j) = *(matrix1 + i*length +j) + *(matrix2 + i*length +j);
		}
	}
	//matrix_print(matrix3,length);
}

void matrix_substract(int * matrix1, int *matrix2, int *matrix3, int length){
	for(int i = 0; i < length; i++){
		for(int j = 0; j < length; j++){
			*(matrix3 + i*length + j) = *(matrix1 + i*length +j) - *(matrix2 + i*length +j);
		}
	}
	//matrix_print(matrix3,length);
}

void matrix_copy(int *matrix1, int x1, int y1, int length, int * matrix3, int copy_length){
	for(int i = 0; i < copy_length; i++){
		for(int j = 0; j < copy_length; j++){
			//printf("%d %d", i, j);
			if(i + x1 < length && j + y1 < length){
		
			
				*(matrix3 + i*copy_length + j) = *(matrix1 + (i + x1)*length + j + y1);
			}else{
				 *(matrix3 + i*copy_length + j) = 0;
			}
		}
	}
}

void matrix_init(int *matrix, int length){
	for(int i = 0; i < length; i++){
		for(int j = 0; j < length; j++){
			*(matrix + i*length + j) = random(10);
		}
	}
}


void normal_square_matrix_mutiply(int *matrix1,int *matrix2, int *matrix3, int length){
	for(int i = 0;i < length; i++){
		for(int j = 0; j < length; j++){
			*(matrix3 + i*length + j) = 0;
			for(int k = 0; k < length; k++){
				//printf("%d ",  *(matrix3 + i*length +j));
				*(matrix3 + i*length +j) += *(matrix1 + i*length + k) * *(matrix2 + k*length + j);
			}
			//printf("\n");
		}
	}
}

//可能不能反复拷贝，释放反而很慢。。。
void Strassen(int *matrix1, int *matrix2, int *matrix3, int length){

	
	if (length == 1){
		*matrix3 = *matrix1 * *matrix2;
		return;
	} 
	
	
	int copy_length = length/2 + length%2;
	int size = copy_length * copy_length;
	int *result = (int *)malloc(sizeof(int)*size*35);
	
	int *A11 = result + size*0;
	int *A21 = result + size*1;
	int *A12 = result + size*2;
	int *A22 = result + size*3;
	int *B11 = result + size*4;
	int *B21 = result + size*5;
	int *B12 = result + size*6;
	int *B22 = result + size*7;
	int *S1 = result + size*8;
	int *S2 = result + size*9;
	int *S3 = result + size*10;
	int *S4 = result + size*11;
	int *S5 = result + size*12;
	int *S6 = result + size*13;
	int *S7 = result + size*14;
	int *S8 = result + size*15;
	int *S9 = result + size*16;
	int *S10 = result + size*18;
	int *P1 = result + size*19;
	int *P2 = result + size*20;
	int *P3 = result + size*21;
	int *P4 = result + size*22;
	int *P5 = result + size*24;
	int *P6 = result + size*25;
	int *P7 = result + size*26;
	int *T1 = result + size*27;
	int *T2 = result + size*28;
	int *T3 = result + size*29;
	int *T4 = result + size*30;
	int *C11 = result + size*31;
	int *C12 = result + size*32;
	int *C21 = result + size*33;
	int *C22 = result + size*34;
	

	 matrix_copy(matrix1, 0, 0, length, A11, copy_length);
 	 matrix_copy(matrix1, copy_length, 0, length, A21, copy_length);
	 matrix_copy(matrix1, 0, copy_length, length, A12, copy_length);
	 matrix_copy(matrix1, copy_length, copy_length, length, A22, copy_length);
	 matrix_copy(matrix2, 0, 0, length, B11, copy_length);
	 matrix_copy(matrix2, copy_length, 0, length, B21, copy_length);
	 matrix_copy(matrix2, 0, copy_length, length, B12, copy_length);
	 matrix_copy(matrix2, copy_length, copy_length, length, B22, copy_length);
/* 	matrix_print(A11, copy_length);
	matrix_print(A12, copy_length);
	matrix_print(A21, copy_length);
	matrix_print(A22, copy_length);
	matrix_print(B11, copy_length);
	matrix_print(B12, copy_length);
	matrix_print(B21, copy_length);
	matrix_print(B22, copy_length); */
	 matrix_substract(B12, B22, S1, copy_length);
	 matrix_add(A11, A12, S2, copy_length);
	 matrix_add(A21, A22, S3, copy_length);
	 matrix_substract(B21 , B11, S4, copy_length);
	 matrix_add(A11 , A22, S5, copy_length);
	 matrix_add(B11 , B22, S6, copy_length);
	 matrix_substract(A12 , A22, S7, copy_length);
	 matrix_add(B21, B22, S8, copy_length);
	 matrix_substract(A11, A21, S9, copy_length);
	 matrix_add(B11 , B12, S10, copy_length);
/* 	matrix_print(S1, copy_length);
	matrix_print(S2, copy_length);
	matrix_print(S3, copy_length);
	matrix_print(S4, copy_length);
	matrix_print(S5, copy_length);
	matrix_print(S6, copy_length);
	matrix_print(S7, copy_length);
	matrix_print(S8, copy_length);
	matrix_print(S9, copy_length);
	matrix_print(S10, copy_length);  */
	
	 Strassen(A11,S1, P1, copy_length);
	 Strassen(S2,B22, P2, copy_length);
	 Strassen(S3, B11, P3, copy_length);
	 Strassen(A22,S4, P4, copy_length);
	 Strassen(S5, S6, P5, copy_length);
	 Strassen(S7, S8, P6, copy_length);
	 Strassen(S9, S10, P7, copy_length);

/* 	matrix_print(P1, copy_length);
	matrix_print(P2, copy_length);
	matrix_print(P3, copy_length);
	matrix_print(P4, copy_length);
	matrix_print(P5, copy_length);
	matrix_print(P6, copy_length);
	matrix_print(P7, copy_length); */

	matrix_add(P5, P4, T1, copy_length);
	matrix_substract(T1, P2, T2, copy_length);
	matrix_add(T2, P6, C11, copy_length);
	matrix_add(P1, P2, C12, copy_length);
	matrix_add(P3, P4, C21, copy_length);
	matrix_add(P5, P1, T3, copy_length);
	matrix_substract(T3, P3, T4, copy_length);
	matrix_substract(T4, P7, C22, copy_length);
/*  	matrix_print(C11, copy_length);
	matrix_print(C12, copy_length);
	matrix_print(C21, copy_length);
	matrix_print(C22, copy_length);  */
	
	//matrix_print(C11, copy_length);
 	//copy
	for(int i = 0; i < copy_length; i++){
		for(int j = 0; j < copy_length; j++){
			*(matrix3 + i * length + j) = *(C11 + i*copy_length + j);
		}
	}

	for(int i = 0; i < copy_length; i++){
		for(int j = copy_length; j < length; j++){
			*(matrix3 + i * length + j) = *(C12 + i*copy_length + j-copy_length);
		}
	}

	for(int i = copy_length; i < length; i++){
		for(int j = 0; j < copy_length; j++){
			*(matrix3 + i * length + j) = *(C21 + (i-copy_length)*copy_length + j);
		}
	}

	for(int i = copy_length; i < length; i++){
		for(int j = copy_length; j < length; j++){
			*(matrix3 + i * length + j) = *(C22 + (i-copy_length)*copy_length +  j-copy_length);
		}
	}
	
	//free
 	free(result);
}

int main(int argc,char *argv[])
{
	srand((int)time(0));
	int length;
	scanf("%d", &length);
	
	int *matrix1 = (int*)malloc(sizeof(int)*length*length);
	int *matrix2 = (int*)malloc(sizeof(int)*length*length);
	int *matrix3 = (int*)malloc(sizeof(int)*length*length);
	int *matrix4 = (int*)malloc(sizeof(int)*length*length);
	
	double endtime;
	clock_t start,end;
	
	matrix_init(matrix1, length);
	matrix_init(matrix2, length);
	
	
	start=clock();		//程序开始计时
	normal_square_matrix_mutiply(matrix1, matrix2, matrix3, length);
	end=clock();
	endtime = (double)(end-start)/CLOCKS_PER_SEC;
	printf("normal time %f \n", endtime);
	
	start=clock();	
	Strassen(matrix1, matrix2, matrix4, length);
	end=clock();
	endtime = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Strassen time %f \n", endtime);
	
	//int *matrix4 = matrix_copy(matrix3, length/2 + length%2, length/2 + length%2, length,length/2 + length % 2);
/* 	int *matrix5 = matrix_add(matrix1, matrix2, length);
	int *matrix6 = matrix_substract(matrix1, matrix2, length); */
	if(length < 15){
		printf("matrix 1 \n");
		matrix_print(matrix1, length);
		printf("matrix 2\n");
		matrix_print(matrix2, length);
		printf("matrix 3 \n");
		matrix_print(matrix3, length);
		printf("matrix 4\n");
		//matrix_print(matrix4, length/2 + length % 2) ;
		matrix_print(matrix4, length) ;
	/* 	printf("matrix 5 \n");
		matrix_print(matrix5, length);
		printf("matrix 6\n");
		matrix_print(matrix6, length); */
	}


	free(matrix1);
	free(matrix2);
	free(matrix3);
	free(matrix4);

	return 0;
}
