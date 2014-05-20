#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE_IN 2048
#define SIZE_COEF 5
#define PRECISION 8 //The precision is binary (i.e. 2^PRECISION values after the comma are considered)

#define DEBUG 1
#define PRINT_MATLAB 0

extern int fir_proc(int* s_in, int size_in, int* coef, int size_coef, int* s_out);

int s_in[SIZE_IN];
int s_out[SIZE_IN];
int coef[SIZE_COEF];

int main(int argc, char* argv){
        //Generates the input
	for (int i = 0; i < SIZE_IN; i++){
		s_in[i] = i << PRECISION;
		if(DEBUG) printf("%d ", s_in[i]);
	}
        if(DEBUG || PRINT_MATLAB) printf("\n");
        //Generates the coeficients
	for (int i = 0; i < SIZE_COEF; i++){
		coef[i] = (1 << PRECISION) / (SIZE_COEF);
		if(DEBUG) printf("%d ", coef[i]);
	}
        if(DEBUG || PRINT_MATLAB) printf("\n");
        //Calculates the result
        int res = fir_proc(s_in, SIZE_IN, coef, SIZE_COEF, s_out);
        //Prints the result
	for (int i = 0; i < res; i++){
                /*Calculates the fixed-point value of the result (considering 
                  that the multiplication of 2 fixed-point numbers generates 
                  another one with double the original precision).*/
                int fixed_point_value = s_out[i] >> PRECISION;
                if(DEBUG) printf("%d/",s_out[i]);
                if(DEBUG) printf("%d/",fixed_point_value);
                /*Prints the real value of the result. 
                  The result is converted to floating-point.*/
		printf("%.3f ", (float) fixed_point_value / (float) pow(2, PRECISION));
	}
	printf("\n");
}