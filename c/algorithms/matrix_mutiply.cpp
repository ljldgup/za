#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x) (rand()%x)

void matrix_print(int *matrix, int length){
	for(int i = 0; i < length; i++){
		for(int j = 0; j < length; j++){
			printf("%d\t", *(matrix + i*length + j));
		}
		printf("\n");
	}
	printf("-----------------------------\n");
}


int* matrix_add(int * matrix1, int *matrix2,  int length){
	int * matrix3 = (int *)malloc(sizeof(int)*length*length);
	for(int i = 0; i < length; i++){
		for(int j = 0; j < length; j++){
			*(matrix3 + i*length + j) = *(matrix1 + i*length +j) + *(matrix2 + i*length +j);
		}
	}
	//matrix_print(matrix3,length);
	return matrix3;
}

int* matrix_substract(int * matrix1, int *matrix2, int length){
	int * matrix3 = (int *)malloc(sizeof(int)*length*length);
	for(int i = 0; i < length; i++){
		for(int j = 0; j < length; j++){
			*(matrix3 + i*length + j) = *(matrix1 + i*length +j) - *(matrix2 + i*length +j);
		}
	}
	//matrix_print(matrix3,length);
	return matrix3;
}

int *matrix_copy(int *matrix1, int x1, int y1, int length, int copy_length){
	int * matrix3 = (int *)malloc(sizeof(int) * copy_length * copy_length);
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
	return matrix3;
}

void matrix_init(int *matrix, int length){
	for(int i = 0; i < length; i++){
		for(int j = 0; j < length; j++){
			*(matrix + i*length + j) = random(10);
		}
	}
}


int* normal_square_matrix_mutiply(int *matrix1,int *matrix2, int length){
	int *matrix3 = (int*)malloc(sizeof(int) * length * length);
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
	return matrix3;
}

//可能不能反复拷贝，释放反而很慢。。。
int * Strassen(int *matrix1, int *matrix2, int length){
	
	if (length == 1){
		int *result = (int *)malloc(sizeof(int) * 1);
		*result = *matrix1 * *matrix2;
		return result;
	}

	int copy_length = length/2 + length%2;
	int *A11 = matrix_copy(matrix1, 0, 0, length, copy_length);
 	int *A21 = matrix_copy(matrix1, copy_length, 0, length, copy_length);
	int *A12 = matrix_copy(matrix1, 0, copy_length, length, copy_length);
	int *A22 = matrix_copy(matrix1, copy_length, copy_length, length, copy_length);
	int *B11 = matrix_copy(matrix2, 0, 0, length, copy_length);
	int *B21 = matrix_copy(matrix2, copy_length, 0, length, copy_length);
	int *B12 = matrix_copy(matrix2, 0, copy_length, length, copy_length);
	int *B22 = matrix_copy(matrix2, copy_length, copy_length, length, copy_length);
/* 	matrix_print(A11, copy_length);
	matrix_print(A12, copy_length);
	matrix_print(A21, copy_length);
	matrix_print(A22, copy_length);
	matrix_print(B11, copy_length);
	matrix_print(B12, copy_length);
	matrix_print(B21, copy_length);
	matrix_print(B22, copy_length); */
	int *S1 = matrix_substract(B12, B22, copy_length);
	int *S2 = matrix_add(A11, A12, copy_length);
	int *S3 = matrix_add(A21, A22, copy_length);
	int *S4 = matrix_substract(B21 , B11, copy_length);
	int *S5 = matrix_add(A11 , A22, copy_length);
	int *S6 = matrix_add(B11 , B22, copy_length);
	int *S7 = matrix_substract(A12 , A22, copy_length);
	int *S8 = matrix_add(B21, B22, copy_length);
	int *S9 = matrix_substract(A11, A21, copy_length);
	int *S10 = matrix_add(B11 , B12, copy_length);
	int *P1 = Strassen(A11,S1, copy_length);
	int *P2 = Strassen(S2,B22, copy_length);
	int *P3 = Strassen(S3, B11, copy_length);
	int *P4 = Strassen(A22,S4, copy_length);
	int *P5 = Strassen(S5, S6, copy_length);
	int *P6 = Strassen(S7, S8, copy_length);
	int *P7 = Strassen(S9, S10, copy_length);
/* 	matrix_print(S1, copy_length);
	matrix_print(S2, copy_length);
	matrix_print(S3, copy_length);
	matrix_print(S4, copy_length);
	matrix_print(S5, copy_length);
	matrix_print(S6, copy_length);
	matrix_print(S7, copy_length);
	matrix_print(S8, copy_length);
	matrix_print(S9, copy_length);
	matrix_print(S10, copy_length); 
	matrix_print(P1, copy_length);
	matrix_print(P2, copy_length);
	matrix_print(P3, copy_length);
	matrix_print(P4, copy_length);
	matrix_print(P5, copy_length);
	matrix_print(P6, copy_length);
	matrix_print(P7, copy_length);*/

	int *t1, *t2;
	t1 = matrix_add(P5, P4, copy_length);
	t2 = matrix_substract(t1, P2, copy_length);
	int *C11 = matrix_add(t2, P6, copy_length);
	free(t1);free(t2);
	int *C12 = matrix_add(P1, P2, copy_length);
	int *C21 = matrix_add(P3, P4, copy_length);
	t1 = matrix_add(P5, P1, copy_length);
	t2 = matrix_substract(t1, P3, copy_length);
	int *C22 = matrix_substract(t2, P7, copy_length);
	free(t1);free(t2);
/* 	matrix_print(C11, copy_length);
	matrix_print(C12, copy_length);
	matrix_print(C21, copy_length);
	matrix_print(C22, copy_length); */
	
	//matrix_print(C11, copy_length);
	int *result = (int *)malloc(sizeof(int) * length * length);
 	//copy
	for(int i = 0; i < copy_length; i++){
		for(int j = 0; j < copy_length; j++){
			*(result + i * length + j) = *(C11 + i*copy_length + j);
		}
	}

	for(int i = 0; i < copy_length; i++){
		for(int j = copy_length; j < length; j++){
			*(result + i * length + j) = *(C12 + i*copy_length + j-copy_length);
		}
	}

	for(int i = copy_length; i < length; i++){
		for(int j = 0; j < copy_length; j++){
			*(result + i * length + j) = *(C21 + (i-copy_length)*copy_length + j);
		}
	}

	for(int i = copy_length; i < length; i++){
		for(int j = copy_length; j < length; j++){
			*(result + i * length + j) = *(C22 + (i-copy_length)*copy_length +  j-copy_length);
		}
	}
	
	//free
 	free(A11);free(A21);free(A12);free(A22);free(B11);free(B21);free(B12);free(B22);
	free(S1);free(S2);free(S3);free(S4);free(S5);free(S6);free(S7);free(S8);free(S9);free(S10);
	free(P1);free(P2);free(P3);free(P4);free(P5);free(P6);free(P7); 

	return result;

}

int main(int argc,char *argv[])
{
	srand((int)time(0));
	int length = 500; 
	int *matrix1 = (int*)malloc(sizeof(int)*length*length);
	int *matrix2 = (int*)malloc(sizeof(int)*length*length);

	
	double endtime;
	clock_t start,end;
	
	matrix_init(matrix1, length);
	matrix_init(matrix2, length);
	
	
	start=clock();		//程序开始计时
	int *matrix3 = normal_square_matrix_mutiply(matrix1, matrix2, length);
	end=clock();
	endtime = (double)(end-start)/CLOCKS_PER_SEC;
	printf("normal time %f \n", endtime);
	
	start=clock();	
	int *matrix4 = Strassen(matrix1, matrix2, length);
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
