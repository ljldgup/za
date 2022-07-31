#include<stdio.h>
#include<stdlib.h>
#include<time.h>

const long MAXELEMS = 1024*1024*256;
long data[MAXELEMS]={0}; /* The global array we'll be traversing */


 /* test - Iterate over first Melems" elements of array "data" with
 * stride of "stride", using 4 x 4 loop unrolling.
 */
 int test(int elems, int stride)
 {
	 long i, sx2 = stride*2, sx3 = stride*3, sx4 = stride*4;
	 long accO = 0, accl = 0, acc2 = 0, acc3 = 0;
	 long length = elems;
	 long limit = length - sx4;

	 /* Combine 4 elements at a time */
	 for(i = 0; i < limit; i += sx4){
		 accO = accO + data[i];
		 accl = accl + data[i+stride];
		 acc2 = acc2 + data[i+sx2];
		 acc3 = acc3 + data[i+sx3];
	 }


/* Finish any remaining elements */
	for(; i < length; i+=stride){
		accO = accO + data[i];
	}
	
	return((accO + accl) +(acc2 + acc3));
 }




 /* run - Run test(elems, stride) and return read throughput(MB/s).
 * "size" is in bytes, "stride" is in array elements, and Mhz is
 * CPU clock frequency in Mhz.
 */
 double run(int size, int stride)
 {
 int elems = size / sizeof(long);

 test(elems, stride); /* Warm up the cache */

 	long start = clock();	
 	 test(elems, stride); /* Warm up the cache */
 	long end = clock();
	return (size / stride)/(end-start+1.0);
 }
 
 int main(){
 		 	for(int j=128*1024; j <= 128*1024*1024;j*=2){
 	for(int i = 1; i < 13;i++){

		 	double rst = run(j,i);
		 	printf("%d %d %f\n", i, j/1024, rst);
		 }
	 }
 } 
