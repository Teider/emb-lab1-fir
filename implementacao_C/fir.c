#include <stdio.h>
#include <stdlib.h>

//TODO: usar float ou ponto fixo
//int fir(int x[], int size_i, int b[], int N, int y[]){
//	for (int n = N - 1; n < size_i; n++){
//		int sum = 0;
//		for (int k = 0; k <= N - 1; k++){
//			sum += b[k] * x[n - k];
//		}
//		y[n] = sum;
//	}
//	const int LEN_OUT = size_i - (N - 1);
//	return LEN_OUT;
//}

int fir(float x[], int size_i, float b[], int N, float y[]){
	for (int n = N - 1; n < size_i; n++){
		float sum = 0;
		for (int k = 0; k <= N - 1; k++){
			sum += b[k] * x[n - k];
		}
		y[n] = sum;
	}
	const int LEN_OUT = size_i - (N - 1);
	return LEN_OUT;
}

int main(int argc, char* argv){
	const int size_i = 2048;
	const int N = 5;
	float x[size_i];
	float y[size_i];
	float b[N];


	for (int i = 0; i < size_i; i++){
		x[i] = (float)i;
		//printf("%f ", x[i]);
	}
	for (int i = 0; i < N; i++){
		b[i] = 1 / (float)(N + 1);
		//printf("%f ", b[i]);
	}

	int res = fir(x, size_i, b, N, y);

	for (int i = size_i - res; i < size_i; i++){
		printf("%f ", y[i]);
	}
	printf("\n");
	//system("pause");
}
