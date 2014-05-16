extern int fir_proc(int* s_in, int size_in, int* coef, int size_coef, int* s_out);

int main() {
  int s_in[5] = {1,2,3,4,5};
  int size_in = 5;
  int coef[2] = {1,2};
  int size_coef = 2;
  int s_out[5] = {1,2,3,4,5};
  int i;
  int aux;
  i = fir_proc(s_in, size_in, coef, size_coef, s_out);
  for (int j = 0; j < i; j++) {
    aux = s_out[i];
  }
  return 0;
}