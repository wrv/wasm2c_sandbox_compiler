#include <stdio.h>
#include <stdlib.h>

#include "wasm_simd_intrinsics_lib.wasm2c.h"

// Arithmetic Operations

void abs_i32x4(s32* in_a) {
  s32 out[4];
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i res = _mm_abs_epi32(a);
  _mm_storeu_si128((__m128i*) out, res);
  printf("|(%d %d %d %d)| = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}

void add_i32x4(s32* in_a, s32* in_b){
  s32 out[4];
  
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  __m128i res = _mm_add_epi32(a, b);
  _mm_storeu_si128((__m128i*) out, res);

  printf("Add arrays: (%d %d %d %d) + (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}

void dot_i32x4(s32* in_a, s32* in_b) {
    s32 out[4];
  
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  
  // TODO: adjust this
  __m128i res = _mm_add_epi32(a, b);

  _mm_storeu_si128((__m128i*) out, res);

  printf("Add arrays: (%d %d %d %d) + (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


void multiply_i32x4(s32* in_a, s32* in_b){
  s32 out[4];
  
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  __m128i res = _mm_mullo_epi32(a, b);
  _mm_storeu_si128((__m128i*) out, res);

  printf("Multiply arrays: (%d %d %d %d) x (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}

void neg_i32x4(s32* in_a) {
  s32 out[4];
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  // negation is subtracting from 0 - two instructions
  __m128i res = _mm_sub_epi32(_mm_set1_epi32(0.0),a);
  _mm_storeu_si128((__m128i*) out, res);
  printf("neg(%d %d %d %d)| = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}

void sub_i32x4(s32* in_a, s32* in_b){
  s32 out[4];
  
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  __m128i res = _mm_sub_epi32(a, b);
  _mm_storeu_si128((__m128i*) out, res);

  printf("Sub arrays: (%d %d %d %d) - (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}

// Bit-wise operations

void and_v128(s32* in_a, s32* in_b){
  s32 out[4];
  
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  __m128i res = _mm_and_si128(a, b);
  _mm_storeu_si128((__m128i*) out, res);

  printf("And arrays: (%d %d %d %d) & (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}

void andnot_v128(s32* in_a, s32* in_b){
  s32 out[4];
  
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  __m128i res = _mm_andnot_si128(a, b);
  _mm_storeu_si128((__m128i*) out, res);

  printf("Andnot arrays: !(%d %d %d %d) & (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}

void or_v128(s32* in_a, s32* in_b){
  s32 out[4];
  
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  __m128i res = _mm_or_si128(a, b);
  _mm_storeu_si128((__m128i*) out, res);

  printf("Or arrays: (%d %d %d %d) | (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}

void xor_v128(s32* in_a, s32* in_b){
  s32 out[4];
  
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  __m128i res = _mm_xor_si128(a, b);
  _mm_storeu_si128((__m128i*) out, res);

  printf("Xor arrays: (%d %d %d %d) ^ (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}

void not_v128(s32* in_a){
  s32 out[4];
  
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i res = _mm_xor_si128(a, _mm_set1_epi32(-1));
  _mm_storeu_si128((__m128i*) out, res);

  printf("Not array: !(%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}

// comparison operations
void eq_i32x4(int* in_a, int* in_b) {
  s32 out[4];

  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  __m128i res = _mm_cmpeq_epi32(a, b);
  _mm_storeu_si128((__m128i*) out, res);

  printf("Equal arrays: (%d %d %d %d) == (%d %d %d %d)? = (%d %d %d %d)  \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}

void ne_i32x4(int* in_a, int* in_b) {
  s32 out[4];

  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  //__m128i res = _mm_cmpneq_ps(a, b);
  //_mm_storeu_si128((__m128i*) out, res);
  //
  //printf("Not equal arrays: (%d %d %d %d) =! (%d %d %d %d)? = (%d %d %d %d)  \n", 
  //    in_a[0], in_a[1], in_a[2], in_a[3], 
  //    in_b[0], in_b[1], in_b[2], in_b[3], 
  //    out[0], out[1], out[2], out[3]);     
}

void gt_i32x4(int* in_a, int* in_b) {
  s32 out[4];

  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  __m128i res = _mm_cmpgt_epi32(a, b);
  _mm_storeu_si128((__m128i*) out, res);
  
  printf("GT arrays: (%d %d %d %d) > (%d %d %d %d)? = (%d %d %d %d)  \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);     
}


void lt_i32x4(int* in_a, int* in_b) {
  s32 out[4];

  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  __m128i res = _mm_cmplt_epi32(a, b);
  _mm_storeu_si128((__m128i*) out, res);
  
  printf("LT arrays: (%d %d %d %d) < (%d %d %d %d)? = (%d %d %d %d)  \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);     
}

int main(int argc, char** argv) {
  /* Make sure there is at least one command-line argument. */
  if (argc < 2) {
    printf("Usage: %s <number>\n", argv[0]);

    return 1;
  }

  s32 x = atoi(argv[1]);

  // Run it locally without the sandbox
  s32 in_a[4] = {x, x, x, x}; 
  s32 in_a_neg[4] = {-x, -x, -x, -x}; 
  s32 in_a_alt[4] = {x, -x, x, -x}; 
  s32 in_b[4] = {2*x, 2*x, 2*x, 2*x}; 
  int size = 4;

  printf("\t in_a = %d %d %d %d\n", in_a[0], in_a[1], in_a[2], in_a[3]);
  printf("\t in_a_neg = %d %d %d %d\n", in_a_neg[0], in_a_neg[1], in_a_neg[2], in_a_neg[3]);
  printf("\t in_a_alt = %d %d %d %d\n", in_a_alt[0], in_a_alt[1], in_a_alt[2], in_a_alt[3]);
  printf("\t in_b = %d %d %d %d\n", in_b[0], in_b[1], in_b[2], in_b[3]);

  printf("-----------------------------\n");
  printf("Running non-sandboxed SIMD\n");
  // Arithmetic
  printf("- Arithmetic Operations\n");
  abs_i32x4(in_a);
  abs_i32x4(in_a_neg);
  add_i32x4(in_a, in_b);
  multiply_i32x4(in_a, in_b);
  neg_i32x4(in_a);
  neg_i32x4(in_a_neg);
  sub_i32x4(in_a, in_b);
  // Boolean
  printf("- Boolean Operations\n");
  and_v128(in_a, in_b);
  andnot_v128(in_a, in_b);
  or_v128(in_a, in_b);
  xor_v128(in_a, in_b);
  not_v128(in_a);
  // Comparision
  eq_i32x4(in_a, in_b);
  eq_i32x4(in_a, in_a);
  eq_i32x4(in_a, in_a_alt);

  gt_i32x4(in_b, in_a);
  gt_i32x4(in_a, in_a);
  gt_i32x4(in_a_alt, in_a);

  lt_i32x4(in_b, in_a);
  lt_i32x4(in_a, in_a);
  lt_i32x4(in_a_alt, in_a);
  

  // call WASM sandbox
  printf("-----------------------------\n");
  printf("Running WASM sandboxed SIMD\n");
  /* Retrieve sandbox details */
  wasm2c_sandbox_funcs_t sbx_details = get_wasm2c_sandbox_info();

  /* One time initializations of minimum wasi runtime supported by wasm2c */
  sbx_details.wasm_rt_sys_init();

  /* Optional upper limit for number of wasm pages for this module.
  0 means no limit  */
  int max_wasm_page = 0;

  /* Create a sandbox instance */
  wasm2c_sandbox_t* sbx_instance = (wasm2c_sandbox_t*) sbx_details.create_wasm2c_sandbox(max_wasm_page);
  //printf("Malloc'ing input a in Sandbox memory\n");
  /* Pass in in_a and in_b pointers to sandbox memory */
  u32 sbx_in_a = w2c_malloc(sbx_instance, size*sizeof(x));
  u32 sbx_in_a_neg = w2c_malloc(sbx_instance, size*sizeof(x));
  u32 sbx_in_a_alt = w2c_malloc(sbx_instance, size*sizeof(x));
  //printf("Malloc'ing input b in Sandbox memory\n");
  u32 sbx_in_b = w2c_malloc(sbx_instance, size*sizeof(x));

  
  //w2c_memcpy(sbx_instance, sbx_in_a, &in_a[0], size);
  //w2c_memcpy(sbx_instance, sbx_in_a_neg, &in_a_neg[0], size);
  //w2c_memcpy(sbx_instance, sbx_in_b, &in_b[0], size);
  //w2c_memcpy(sbx_instance, sbx_in_a_alt, &in_a_alt, size);
  

  //printf("Copying values into malloced memory\n");
  // TODO: figure out how to properly pass in values - doesn't seem to work with values larger than 1 byte
  for (int i = 0; i < size; i++) {
    w2c_memset(sbx_instance, sbx_in_a + sizeof(x) * i,   x, 1); //sizeof(x));
    w2c_memset(sbx_instance, sbx_in_a_neg + sizeof(x) * i,  -x, 1); //sizeof(x));
    w2c_memset(sbx_instance, sbx_in_b + sizeof(x) * i, 2*x, 1); //sizeof(x));
    if (i %2 == 0) {
      w2c_memset(sbx_instance, sbx_in_a_alt + sizeof(x) * i,  x, 1); //sizeof(x));
    } else {
      w2c_memset(sbx_instance, sbx_in_a_alt + sizeof(x) * i, -x, 1); //sizeof(x));
    }
  }
  
  printf("- Arithmetic Operations\n");
  w2c_abs_i32x4(sbx_instance, sbx_in_a);
  w2c_abs_i32x4(sbx_instance, sbx_in_a_neg);
  w2c_add_i32x4(sbx_instance, sbx_in_a, sbx_in_b);
  w2c_multiply_i32x4(sbx_instance, sbx_in_a, sbx_in_b);
  w2c_neg_i32x4(sbx_instance, sbx_in_a);
  w2c_neg_i32x4(sbx_instance, sbx_in_a_neg);
  w2c_sub_i32x4(sbx_instance, sbx_in_a, sbx_in_b);


  printf("- Bit-wise Operations\n");
  w2c_and_v128(sbx_instance, sbx_in_a, sbx_in_b);
  w2c_andnot_v128(sbx_instance, sbx_in_a, sbx_in_b);
  w2c_or_v128(sbx_instance, sbx_in_a, sbx_in_b);
  w2c_xor_v128(sbx_instance, sbx_in_a, sbx_in_b);
  w2c_not_v128(sbx_instance, sbx_in_a);

  printf("- Comparison Operations\n");
  w2c_eq_i32x4(sbx_instance, sbx_in_a, sbx_in_b);
  w2c_eq_i32x4(sbx_instance, sbx_in_a, sbx_in_a);
  w2c_eq_i32x4(sbx_instance, sbx_in_a, sbx_in_a_alt);
  w2c_ne_i32x4(sbx_instance, sbx_in_a, sbx_in_b);
  w2c_ne_i32x4(sbx_instance, sbx_in_a, sbx_in_a);
  w2c_ne_i32x4(sbx_instance, sbx_in_a, sbx_in_a_alt);
  w2c_gt_i32x4(sbx_instance, sbx_in_b, sbx_in_a);
  w2c_gt_i32x4(sbx_instance, sbx_in_a, sbx_in_a);
  w2c_gt_i32x4(sbx_instance, sbx_in_a_alt, sbx_in_a);
  w2c_lt_i32x4(sbx_instance, sbx_in_b, sbx_in_a);
  w2c_lt_i32x4(sbx_instance, sbx_in_a, sbx_in_a);
  w2c_lt_i32x4(sbx_instance, sbx_in_a_alt, sbx_in_a);
  
  w2c_all_the_f32x4(sbx_instance, sbx_in_a, sbx_in_b);
  w2c_all_the_f64x2(sbx_instance, sbx_in_a, sbx_in_b);
  w2c_all_the_i16x8(sbx_instance, sbx_in_a, sbx_in_b);

  /* Destroy the sandbox instance */
  sbx_details.destroy_wasm2c_sandbox(sbx_instance);

  return 0;
}