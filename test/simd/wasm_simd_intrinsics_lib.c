#include <wasm_simd128.h>

void multiply_arrays(int* out, int* in_a, int* in_b, int size) {
  for (int i = 0; i < size; i += 4) {
    v128_t a = wasm_v128_load(&in_a[i]);
    v128_t b = wasm_v128_load(&in_b[i]);
    v128_t prod = wasm_i32x4_mul(a, b);
    wasm_v128_store(&out[i], prod);
  }
}

void multiply_4x4_arrays(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(&in_a[i]);
  v128_t b = wasm_v128_load(&in_b[i]);
  v128_t prod = wasm_i32x4_mul(a, b);
  wasm_v128_store(out, prod);
  printf("(%d %d %d %d) x (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
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
