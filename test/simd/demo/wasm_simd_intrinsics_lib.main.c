#include <stdio.h>
#include <stdlib.h>

#include "wasm_simd_intrinsics_lib.wasm2c.h"

int main(int argc, char** argv) {
  /* Make sure there is at least one command-line argument. */
  if (argc < 2) {
    printf("Usage: %s <number>\n", argv[0]);

    return 1;
  }

  s32 x = atoi(argv[1]);

  // Run it locally without the sandbox
  s32 in_a[4] = {x, x, x, x}; 
  s32 in_b[4] = {2*x, 2*x, 2*x, 2*x}; 
  s32 out[4];

  printf("in_a = %d %d %d %d\n", in_a[0], in_a[1], in_a[2], in_a[3]);
  printf("in_b = %d %d %d %d\n", in_b[0], in_b[1], in_b[2], in_b[3]);


  printf("Running non-sandboxed SIMD\n");
  __m128i a = _mm_loadu_si128((__m128i*) in_a);
  //printf("hi\n");
  __m128i b = _mm_loadu_si128((__m128i*) in_b);
  //printf("hi2\n");
  __m128i res = _mm_mullo_epi32(a, b);
  //printf("hi3\n");
  _mm_storeu_si128((__m128i*) out, res);
  //printf("hi4\n");

  printf("(%d %d %d %d) x (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);

  // call WASM sandbox

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

  /* Call `fac`, using the mangled name. */
  w2c_multiply_4x4_arrays(sbx_instance, x);

  /* Print the result. */
  //printf("w2c_multiply_4x4_arrays(%u %u %u %u x %u %u %u %u) = (%d %d %d %d)\n", 
  //      x, x, x, x, 
  //      2*x, 2*x, 2*x, 2*x, 
  //      out[0], out[1], out[2], out[3]);

  /* Destroy the sandbox instance */
  sbx_details.destroy_wasm2c_sandbox(sbx_instance);



  return 0;
}