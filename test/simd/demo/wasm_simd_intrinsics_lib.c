#include <wasm_simd128.h>
#include <stdio.h>

/* Arithmetic Operations */

void abs_i32x4(int* in_a) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t prod = wasm_i32x4_abs(a);
  wasm_v128_store(out, prod);
  fprintf(stderr, "|(%d %d %d %d)| = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}


void add_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_add(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Add arrays: (%d %d %d %d) + (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


void multiply_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_mul(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Multiply arrays: (%d %d %d %d) x (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


void neg_i32x4(int* in_a) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t prod = wasm_i32x4_neg(a);
  wasm_v128_store(out, prod);
  fprintf(stderr, "neg(%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}


void sub_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_sub(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Sub arrays: (%d %d %d %d) - (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


/* Bit-wise Operations */

void and_v128(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_v128_and(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "And arrays: (%d %d %d %d) & (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}

void or_v128(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_v128_or(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Or arrays: (%d %d %d %d) | (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}

void xor_v128(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_v128_xor(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Xor arrays: (%d %d %d %d) ^ (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}

void not_v128(int* in_a) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t prod = wasm_v128_not(a);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Not array: !(%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}
