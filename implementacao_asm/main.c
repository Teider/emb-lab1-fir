#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Debug options (1=activated, 0=deactivated)
#define DEBUG 0 //misc debug messages
#define DEBUG_C 1 //comparison with C FIR function
#define PRINT_MATLAB 1 //Matlab output


#define SIZE_IN 1000
#define SIZE_COEF 5
#define PRECISION 12 //The precision is binary (i.e. 2^PRECISION values after the comma are considered)

//Assembly function for the FIR filter
extern int fir_proc(int* s_in, int size_in, int* coef, int size_coef, int* s_out);

//C function for the FIR filter
int fir_c(int s_in[], int size_in, int coef[], int size_coef, int s_out[]){
    for (int n = size_coef-1; n < size_in; n++){
        int sum = 0;
        for (int k = 0; k < size_coef; k++){
            sum += coef[k] * s_in[n - k];
        }
        s_out[n - (size_coef-1)] = sum;
    }
    const int LEN_OUT = size_in - (size_coef - 1);
    return LEN_OUT;
}


int s_in[SIZE_IN];
int s_out[SIZE_IN];
int s_out_C[SIZE_IN];
int coef[SIZE_COEF];

int main(int argc, char* argv){
    //
    //Generates the input
    //
    if(PRINT_MATLAB) printf("s_in=[");
    for (int i = 0; i < SIZE_IN; i++){
        double value = (double) i / 10; //floating-point value
        s_in[i] = (int) round(value * pow(2,PRECISION)); //fixed-point value (One 'PRECISION' more)
        if(PRINT_MATLAB) printf("%f ", value);
        if(DEBUG) printf("%f/", value);     
        if(DEBUG) printf("%f/", value * pow(2,PRECISION));  
        if(DEBUG) printf("%d ", s_in[i]);                
    }
    if(PRINT_MATLAB) printf("];");
    if(DEBUG || PRINT_MATLAB) printf("\n");
    //
    //Generates the coeficients (moving average filter)
    //
    if(PRINT_MATLAB) printf("coef=[");
    for (int i = 0; i < SIZE_COEF; i++){
        coef[i] = (1 << PRECISION) / (SIZE_COEF);  //(One 'PRECISION' more)
        if(PRINT_MATLAB) printf("%f ", (float)1/(float)SIZE_COEF);
        if(DEBUG) printf("%d ", coef[i]);
    }
    if(PRINT_MATLAB) printf("];");
    if(DEBUG || PRINT_MATLAB) printf("\n");
    //
    //Calculates the result
    //
    int res = fir_proc(s_in, SIZE_IN, coef, SIZE_COEF, s_out);
    //
    //Prints the result
    //
    if(PRINT_MATLAB) printf("s_out=[");
    for (int i = 0; i < res; i++){
        /*Calculates the real value of the result (considering 
        that the multiplication of 2 fixed-point numbers generates 
        another one with double the original precision).*/
        int fixed_point_value = s_out[i] >> PRECISION; //(One 'PRECISION' less)
        double floating_point_value = (double) fixed_point_value / (double) pow(2, PRECISION); //(One 'PRECISION' less)
        if(DEBUG) printf("%d/",s_out[i]);
        if(DEBUG) printf("%d/",fixed_point_value);
        /*Prints the real value of the result.*/
        if(DEBUG || PRINT_MATLAB) printf("%.3f ", floating_point_value);
    }
    if(PRINT_MATLAB) printf("];");
    if(DEBUG || PRINT_MATLAB) printf("\n");
    
    
    if(DEBUG_C){
        //
        //Calculates the C function result and compare with the assembly result
        //
        int res_C = fir_c(s_in, SIZE_IN, coef, SIZE_COEF, s_out_C);
        if(res_C != res){
            printf("'res_C' and 'res' are different! (%d, %d)\n", res_C, res);
        }
        for(int i = 0; i < res_C; i++){
            if(s_out_C[i] != s_out[i]){
                printf("s_out_C[%d] != s_out[%d]  --> (%d,%d)", i,i, s_out_C[i], s_out[i]);
            }
        }
    }
}