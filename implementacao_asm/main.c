#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE_IN 2048
#define SIZE_COEF 5
#define PRECISION 8 //The precision is binary (i.e. 2^PRECISION values after the comma are considered)

extern int fir_proc(int* s_in, int size_in, int* coef, int size_coef, int* s_out);

//int fir_c(float s_in[], int size_in, float coef[], int size_coef, float s_out[]){
//	for (int n = 0; n < size_in - 1; n++){
//		float sum = 0;
//		for (int k = 0; k < size_coef; k++){
//			sum += coef[k] * s_in[n - k];
//		}
//		s_out[n] = sum;
//	}
//	const int LEN_OUT = size_in - (size_coef - 1);
//	return LEN_OUT;
//}

int s_in[SIZE_IN];
int s_out[SIZE_IN];
int coef[SIZE_COEF];

int main(int argc, char* argv){
	//const int size_in = 2048;
	//const int size_coef = 5;
	//float s_in[SIZE_IN];
	//float s_out[SIZE_IN];
	//float coef[SIZE_COEF];


	for (int i = 0; i < SIZE_IN; i++){
		s_in[i] = i << PRECISION;
		//printf("%d ", s_in[i]);
	}
        printf("\n");
	for (int i = 0; i < SIZE_COEF; i++){
		coef[i] = (1 << PRECISION) / (SIZE_COEF);
		//printf("%d ", coef[i]);
	}
        printf("\n");
	//int res = fir_c(s_in, SIZE_IN, coef, SIZE_COEF, s_out);
        int res = fir_proc(s_in, SIZE_IN, coef, SIZE_COEF, s_out);
        
	for (int i = 0; i < res; i++){
                /*Calculates the fixed-point value of the result (considering 
                  that the multiplication of 2 fixed-point numbers generates 
                  another one with double the original precision).*/
                int fixed_point_value = s_out[i] >> PRECISION;
                //printf("%d/",s_out[i]);
                //printf("%d/",fixed_point_value);
                /*Prints the real value of the result. 
                  The result is converted to floating-point.*/
		printf("%.3f ", (float) fixed_point_value / (float) pow(2, PRECISION));
	}
	printf("\n");
	//system("pause");
}