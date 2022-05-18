#include <wasm_simd128.h>
#include <stdio.h>

void multiply_arrays(int* out, int* in_a, int* in_b, int size) {
  for (int i = 0; i < size; i += 4) {
    v128_t a = wasm_v128_load(&in_a[i]);
    v128_t b = wasm_v128_load(&in_b[i]);
    v128_t prod = wasm_i32x4_mul(a, b);
    wasm_v128_store(&out[i], prod);
  }
}

void add_arrays(int* out, int* in_a, int* in_b, int size) {
  for (int i = 0; i < size; i += 4) {
    v128_t a = wasm_v128_load(&in_a[i]);
    v128_t b = wasm_v128_load(&in_b[i]);
    v128_t prod = wasm_i32x4_add(a, b);
    wasm_v128_store(&out[i], prod);
  }
}

void multiply_loaded_arrays(int* out, v128_t a, v128_t b, int size) {
  for (int i = 0; i < size; i += 4) {
    v128_t prod = wasm_i32x4_mul(a, b);
    wasm_v128_store(&out[i], prod);
  }
}

int main(int argc, const char *argv[]) {
  int size = 4;
  
  int in_a[4]    = {1, 2, 3, 4}; 
  int in_b[4]    = {2, 3, 4, 5}; 
  int mul_res[4] = {2, 6, 12, 20};
  int add_res[4] = {3, 5, 7, 9};
  int out[4];
  
  //v128_t splat3 = wasm_i32x4_const_splat(4);
  //v128_t splat10 = wasm_i32x4_const_splat(10);
  //multiply_loaded_arrays(out, splat3, splat10, size);
  //printf("multiply_splat: splat(4) x splat(10) = %d %d %d %d \n", 
  //         out[0], out[1], out[2], out[3]);

  multiply_arrays(out, in_a, in_b, size);
  printf("multiply: [%d %d %d %d] x [%d %d %d %d] = %d %d %d %d \n", 
           in_a[0], in_a[1], in_a[2], in_a[3],
           in_b[0], in_b[1], in_b[2], in_b[3],
           out[0], out[1], out[2], out[3]);

  int mul_stat = mul_res[0] == out[0] && 
                 mul_res[1] == out[1] && 
                 mul_res[2] == out[2] && 
                 mul_res[3] == out[3];

  add_arrays(out, in_a, in_b, size);
  printf("add: [%d %d %d %d] + [%d %d %d %d] = %d %d %d %d \n", 
           in_a[0], in_a[1], in_a[2], in_a[3],
           in_b[0], in_b[1], in_b[2], in_b[3],
           out[0], out[1], out[2], out[3]);

  int add_stat = add_res[0] == out[0] && 
                 add_res[1] == out[1] && 
                 add_res[2] == out[2] && 
                 add_res[3] == out[3];

  return mul_stat != 1 && add_stat != 1;
}