#include <wasm_simd128.h>
#include <stdio.h>


/* V128 Operations */

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


void andnot_v128(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_v128_andnot(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Andnot arrays: !(%d %d %d %d) & (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}

/*
void anytrue_v128(int* in_a) {
  v128_t a = wasm_v128_load(in_a);
  bool prod = wasm_v128_any_true(a);
  fprintf(stderr, "Any true (%d %d %d %d) = %d \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      prod);
}
*/


void bitselect_v128(int* in_a, int* in_b, int* in_mask) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t mask = wasm_v128_load(in_mask);
  v128_t prod = wasm_v128_bitselect(a, b, mask);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Bitmask (%d %d %d %d) and  (%d %d %d %d) with mask (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      in_mask[0], in_mask[1], in_mask[2], in_mask[3], 
      out[0], out[1], out[2], out[3]);
}


/*
// requries SimdLoadLaneExpr
void load16_lane_1_v128(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t res = wasm_v128_load16_lane(in_b, a, 1);
  wasm_v128_store(out, res);
  fprintf(stderr, "Load16 Lane from (%d %d %d %d) and  %d into lane 1 = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], 
      out[0], out[1], out[2], out[3]);
}
*/

// requires LoadSplatExpr
void load16_splat_v128(int* in_a) {
  short out[8];
  v128_t res = wasm_v128_load16_splat(in_a);
  wasm_v128_store(out, res);
  fprintf(stderr, "Load16 Splat from %d = (%d %d %d %d %d %d %d %d) \n", 
      in_a[0],
      out[0], out[1], out[2], out[3], out[4], out[5], out[6], out[7]);
}


/*
void load32_lane_1_v128(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t res = wasm_v128_load32_lane(in_b, a, 1);
  wasm_v128_store(out, res);
  fprintf(stderr, "Load32 Lane from (%d %d %d %d) and  %d into lane 1 = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], 
      out[0], out[1], out[2], out[3]);
}
*/

void load32_splat_v128(int* in_a) {
  int out[4];
  v128_t a = wasm_v128_load32_splat(&in_a[0]);
  v128_t b = wasm_v128_load32_splat(&in_a[1]);
  v128_t res = wasm_i32x4_mul(a, b);

  wasm_v128_store(out, res);
  fprintf(stderr, "Load32 Splat from %d = (%d %d %d %d) \n", 
      in_a[0], 
      a[0], a[1], a[2], a[3]);
  
  fprintf(stderr, "Load32 Splat from %d = (%d %d %d %d) \n", 
      in_a[1], 
      b[0], b[1], b[2], b[3]);

  fprintf(stderr, "Mul(a, b) = (%d %d %d %d) \n", 
      out[0], out[1], out[2], out[3]);
  
}

/*
void load32_zero_v128(int* in_a) {
  int out[4];
  v128_t res = wasm_v128_load32_zero(in_a);
  wasm_v128_store(out, res);
  fprintf(stderr, "Load32 Zero from (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}
*/

/*
// Requires SimdStoreLaneExpr
void load64_lane_1_v128(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t res = wasm_v128_load64_lane(in_b, a, 1);
  wasm_v128_store(out, res);
  fprintf(stderr, "Load64 Lane from (%d %d %d %d) and  %d into lane 1 = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], 
      out[0], out[1], out[2], out[3]);
}
*/


void load64_splat_v128(int* in_a) {
  uint64_t out[2];
  v128_t res = wasm_v128_load64_splat(in_a);
  wasm_v128_store(out, res);
  fprintf(stderr, "Load64 Splat from %d = (%lu %lu) \n", 
      in_a[0],
      out[0], out[1]);
}


/*
// Requires SimdStoreLaneExpr
void load64_zero_v128(int* in_a) {
  int out[4];
  v128_t res = wasm_v128_load64_zero(in_a);
  wasm_v128_store(out, res);
  fprintf(stderr, "Load64 Zero from (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}
*/


/*
// Requires SimdLoadLaneExpr
void load8_lane_1_v128(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t res = wasm_v128_load8_lane(in_b, a, 1);
  wasm_v128_store(out, res);
  fprintf(stderr, "Load8 Lane from (%d %d %d %d) and  %d into lane 1 = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], 
      out[0], out[1], out[2], out[3]);
}
*/


void load8_splat_v128(int* in_a) {
  char out[16];
  v128_t res = wasm_v128_load8_splat(in_a);
  wasm_v128_store(out, res);
  fprintf(stderr, "Load8 Splat from %d = (%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d) \n", 
      in_a[0],
      out[0],  out[1],  out[2],  out[3],
      out[4],  out[5],  out[6],  out[7],
      out[8],  out[9],  out[10], out[11],
      out[12], out[13], out[14], out[15]);
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


/*
// Requires SimdStoreLaneExpr
void store16_lane_1_v128(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  wasm_v128_store(out, a);
  wasm_v128_store16_lane(out, b, 1);
  fprintf(stderr, "Store16 Lane 1 from (%d %d %d %d) and (%d %d %d %d) into lane 1 = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}
*/


/*
// Requires SimdStoreLaneExpr
void store32_lane_1_v128(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  wasm_v128_store(out, a);
  wasm_v128_store32_lane(out, b, 1);
  fprintf(stderr, "Store32 Lane 1 from (%d %d %d %d) and (%d %d %d %d) into lane 1 = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}
*/

/*
// requires i8x16_shuffle
void store64_lane_1_v128(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  wasm_v128_store(out, a);
  wasm_v128_store64_lane(out, b, 1);
  fprintf(stderr, "Store64 Lane 1 from (%d %d %d %d) and (%d %d %d %d) into lane 1 = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}
*/

/*
// Requires SimdStoreLaneExpr
void store8_lane_1_v128(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  wasm_v128_store(out, a);
  wasm_v128_store8_lane(out, b, 1);
  fprintf(stderr, "Store8 Lane 1 from (%d %d %d %d) and (%d %d %d %d) into lane 1 = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}
*/


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



/* I32X4 Operations */

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

/*
void alltrue_i32x4(int* in_a) {
  v128_t a = wasm_v128_load(in_a);
  bool out = wasm_i32x4_all_true(a);
  fprintf(stderr, "All true (%d %d %d %d)? = %d \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out);
}
*/

void bitmask_i32x4(int* in_a) {
  v128_t a = wasm_v128_load(in_a);
  int out = wasm_i32x4_bitmask(a);
  fprintf(stderr, "Bitmask (%d %d %d %d) = %d \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], out);
}


void add_const_arr_i32x4(int* in_a) {
  int out[4];
  int in_b[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_i32x4_const(3, 4, 5, 6);
  
  v128_t prod = wasm_i32x4_add(a, b);
  wasm_v128_store(out, prod);
  wasm_v128_store(in_b, b);
  fprintf(stderr, "Add const arr: (%d %d %d %d) + (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


void add_const_splat_5_i32x4(int* in_a) {
  int out[4];
  int in_b[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_i32x4_const_splat(5);
  
  v128_t prod = wasm_i32x4_add(a, b);
  wasm_v128_store(out, prod);
  wasm_v128_store(in_b, b);
  fprintf(stderr, "Add const 5: (%d %d %d %d) + (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);

}


void dot_i16x8_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_dot_i16x8(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Dot product: (%d %d %d %d) < (%d %d %d %d)? = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


void eq_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_eq(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Equal arrays: (%d %d %d %d) == (%d %d %d %d)? = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


void extadd_pairwise_i16x8_i32x4(int* in_a) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t prod = wasm_i32x4_extadd_pairwise_i16x8(a);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Pairwise Add i16x8 arrays: (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}

/*
// Extends the high values into i16x8 types
void extend_high_i16x8_i32x4(int* in_a) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t prod = wasm_i32x4_extend_high_i16x8(a);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Extend high (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}


void extend_low_i16x8_i32x4(int* in_a) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t prod = wasm_i32x4_extend_low_i16x8(a);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Extend low (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}


void extmul_high_i16x8_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_extmul_high_i16x8(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Extmul arrays: (%d %d %d %d) * (%d %d %d %d)? = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


void extmul_low_i16x8_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_extmul_low_i16x8(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Extmul arrays: (%d %d %d %d) * (%d %d %d %d)? = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}
*/

void extract_lane_2_i32x4(int* in_a) {
  v128_t a = wasm_v128_load(in_a);
  // index must be constant
  int out = wasm_i32x4_extract_lane(a, 2);
  fprintf(stderr, "Extract((%d %d %d %d), 2) = %d \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out);
}


void ge_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_ge(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "GE (%d %d %d %d) >= (%d %d %d %d)? = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


void gt_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_gt(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "GT arrays: (%d %d %d %d) > (%d %d %d %d)? = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


void le_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_le(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "LE arrays: (%d %d %d %d) <= (%d %d %d %d)? = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


void lt_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_lt(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "LT arrays: (%d %d %d %d) < (%d %d %d %d)? = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


/*
// requires SimdStoreLaneExpr
void load16x4_i32x4(int* in_a) {
  int out[4];
  v128_t prod = wasm_i32x4_load16x4(in_a);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Load 16x4 array: (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}
*/


void make_i32x4(int* in_a) {
  int out[4];
  v128_t prod = wasm_i32x4_make(in_a[0], in_a[1], in_a[2], in_a[3]);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Make array: (%d %d %d %d) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}


void max_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_max(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Max arrays: (%d %d %d %d) < (%d %d %d %d)? = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3], 
      out[0], out[1], out[2], out[3]);
}


void min_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_min(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Min arrays: (%d %d %d %d) < (%d %d %d %d)? = (%d %d %d %d) \n", 
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


void ne_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  v128_t prod = wasm_i32x4_ne(a, b);
  wasm_v128_store(out, prod);
  fprintf(stderr, "NE arrays: (%d %d %d %d) != (%d %d %d %d)? = (%d %d %d %d) \n", 
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


void replace_lane_1_i32x4(int* in_a, int index, int val) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  // index must be constant
  v128_t prod = wasm_i32x4_replace_lane(a, 1, val);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Replace((%d %d %d %d), %d, %d)  = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], index, val,
      out[0], out[1], out[2], out[3]);
}


void shl_i32x4(int* in_a, int val) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t prod = wasm_i32x4_shl(a, val);
  wasm_v128_store(out, prod);
  fprintf(stderr, "SHL (%d %d %d %d) by %d = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], val,
      out[0], out[1], out[2], out[3]);
}


void shr_i32x4(int* in_a, int val) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t prod = wasm_i32x4_shr(a, val);
  wasm_v128_store(out, prod);
  fprintf(stderr, "SHR (%d %d %d %d) by %d = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], val,
      out[0], out[1], out[2], out[3]);
}

/*
void shuffle_i32x4(int* in_a, int* in_b) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t b = wasm_v128_load(in_b);
  // shuffle values must be constants
  v128_t prod = wasm_i32x4_shuffle(a, b, 0, 1, 3, 2);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Shuffle arrays: (%d %d %d %d) and (%d %d %d %d) by (0 1 3 2) = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      in_b[0], in_b[1], in_b[2], in_b[3],  
      out[0], out[1], out[2], out[3]);
}
*/

void splat_i32x4(int val) {
  int out[4];
  v128_t prod = wasm_i32x4_splat(val);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Splat %d = (%d %d %d %d) \n", 
      val,
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

/*
// floating point to integer conversion 
void trunc_sat_f32x4_i32x4(int* in_a) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t prod = wasm_i32x4_trunc_sat_f32x4(a);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Trunc Sat f32x4 (%d %d %d %d)? = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}
*/

/*
// Requires SimdStoreLaneExpr
void trunc_sat_f64x2_zero_i32x4(int* in_a) {
  int out[4];
  v128_t a = wasm_v128_load(in_a);
  v128_t prod = wasm_i32x4_trunc_sat_f64x2_zero(a);
  wasm_v128_store(out, prod);
  fprintf(stderr, "Trunc Sat f32x4 (%d %d %d %d)? = (%d %d %d %d) \n", 
      in_a[0], in_a[1], in_a[2], in_a[3], 
      out[0], out[1], out[2], out[3]);
}
*/


