
## Skip over #define statements at the top of the file
start_function_mapping = False
start_function_mapping_string = "* Begin function implementations"

## Extract simde function name
initialization_string = "SIMDE_FUNCTION_ATTRIBUTES"
end_string = "#if defined(SIMDE_WASM_SIMD128_ENABLE_NATIVE_ALIASES)"

## Extract mapping
wasm_mapping                 = "if defined(SIMDE_WASM_SIMD128_NATIVE"
# x86
x86_xop_mapping              = "if defined(SIMDE_X86_XOP_NATIVE"        # AMD eXtended Operations
x86_sse_mapping              = "if defined(SIMDE_X86_SSE_NATIVE"
x86_sse2_mapping             = "if defined(SIMDE_X86_SSE2_NATIVE"
x86_ssse3_mapping            = "if defined(SIMDE_X86_SSSE3_NATIVE"    # Intel Supplemental Streaming SIMD Extensions 3
x86_sse41_mapping            = "if defined(SIMDE_X86_SSE4_1_NATIVE"
x86_sse42_mapping            = "if defined(SIMDE_X86_SSE4_2_NATIVE"
x86_avx2_mapping             = "if defined(SIMDE_X86_AVX2_NATIVE"
x86_avx512vl_mapping         = "if defined(SIMDE_X86_AVX512VL_NATIVE" # Intel AVX 512 Vector Length Extensions 
x86_avx512dq_mapping         = "if defined(SIMDE_X86_AVX512DQ_NATIVE" # Intel AVX 512 Doubleword and Quadword Instructions
x86_avx512bitalg_mapping     = "if defined(SIMDE_X86_AVX512BITALG_NATIVE" # Intel AVX 512 Doubleword and Quadword Instructions
# ARM
arm_neon_a32v7_mapping       = "if defined(SIMDE_ARM_NEON_A32V7_NATIVE"
arm_neon_a32v7_nn_mapping    = "if defined(SIMDE_ARM_NEON_A32V7" # nn stands for non-native. Unclear what what the difference is
arm_neon_a32v8_mapping       = "if defined(SIMDE_ARM_NEON_A32V8_NATIVE"
arm_neon_a64v8_mapping       = "if defined(SIMDE_ARM_NEON_A64V8_NATIVE"
# PowerPC / System Z ()
powerpc_altivec_p6_mapping   = "if defined(SIMDE_POWER_ALTIVEC_P6_NATIVE"
powerpc_altivec_p7_mapping   = "if defined(SIMDE_POWER_ALTIVEC_P7_NATIVE"
powerpc_altivec_p8_mapping   = "if defined(SIMDE_POWER_ALTIVEC_P8_NATIVE"
zarch_zvector_13_mapping     = "if defined(SIMDE_ZARCH_ZVECTOR_13_NATIVE"
zarch_zvector_14_mapping     = "if defined(SIMDE_ZARCH_ZVECTOR_14_NATIVE"
# Rely on compiler-provided 
simde_vectorize_mapping      = "SIMDE_VECTORIZE"
simde_convert_vector_mapping = "if defined(SIMDE_CONVERT_VECTOR_"
simde_vector_subscript_mapping = "if defined(SIMDE_VECTOR_SUBSCRIPT"

## Arch-specific inclusion
arch_amd64 = "SIMDE_ARCH_AMD64"

## SIMD-related bugs checked
err1 = "SIMDE_BUG_CLANG_BAD_VGET_SET_LANE_TYPES"
err2 = "SIMDE_BUG_CLANG_50932"

## Stats
mapping_counter = {}

def update_counter(function_arch_extract_mode):
    if function_arch_extract_mode in mapping_counter.keys():
        mapping_counter[function_arch_extract_mode] += 1
    else:
        mapping_counter[function_arch_extract_mode] = 1


src = open('simd128.h', 'r')

# The first element will contain contents from 'start_function_mapping_string' to the first function
function_mappings = []
function_counter = -1
function_line = 0
function_arch_extract_mode = "tbd"
function_active_extract = False

for l in src:
    if start_function_mapping:
        if initialization_string in l:
            function_mappings.append({})
            function_counter += 1
            function_line = 0
            function_arch_extract_mode = "tbd"
            function_active_extract = True
        
        if end_string in l:
            function_active_extract = False
        
        # 0 or higher means we've seen an initialization string
        if function_active_extract:
            if function_line == 1:
                function_mappings[function_counter]["type"] = l.strip()
            elif function_line == 2:
                function_mappings[function_counter]["name"] = l.split('(')[0].strip()
            elif function_line > 2:
                # begin to search for mappings
                if wasm_mapping in l:
                    function_arch_extract_mode = "wasm"
                    update_counter(function_arch_extract_mode)
                elif x86_xop_mapping in l:
                    function_arch_extract_mode = "x86_xop_mapping"
                    update_counter(function_arch_extract_mode)
                elif x86_sse_mapping in l:
                    function_arch_extract_mode = "x86_sse_mapping"
                    update_counter(function_arch_extract_mode)
                elif x86_sse2_mapping in l:
                    function_arch_extract_mode = "x86_sse2_mapping"
                    update_counter(function_arch_extract_mode)
                elif x86_ssse3_mapping in l:
                    function_arch_extract_mode = "x86_ssse3_mapping"
                    update_counter(function_arch_extract_mode)
                elif x86_sse41_mapping in l:
                    function_arch_extract_mode = "x86_sse41_mapping"
                    update_counter(function_arch_extract_mode)
                elif x86_sse42_mapping in l:
                    function_arch_extract_mode = "x86_sse42_mapping"
                    update_counter(function_arch_extract_mode)
                elif x86_avx2_mapping in l:
                    function_arch_extract_mode = "x86_avx2_mapping"
                    update_counter(function_arch_extract_mode)
                elif x86_avx512vl_mapping in l:
                    function_arch_extract_mode = "x86_avx512vl_mapping"
                    update_counter(function_arch_extract_mode)
                elif x86_avx512dq_mapping in l:
                    function_arch_extract_mode = "x86_avx512dq_mapping"
                    update_counter(function_arch_extract_mode)
                elif x86_avx512bitalg_mapping in l:
                    function_arch_extract_mode = "x86_avx512bitalg_mapping"
                    update_counter(function_arch_extract_mode)
                elif arm_neon_a32v7_mapping in l:
                    function_arch_extract_mode = "arm_neon_a32v7_mapping"
                    update_counter(function_arch_extract_mode)
                elif arm_neon_a32v7_nn_mapping in l:
                    function_arch_extract_mode = "arm_neon_a32v7_nn_mapping"
                    update_counter(function_arch_extract_mode)
                elif arm_neon_a32v8_mapping in l:
                    function_arch_extract_mode = "arm_neon_a32v8_mapping"
                    update_counter(function_arch_extract_mode)
                elif arm_neon_a64v8_mapping in l:
                    function_arch_extract_mode = "arm_neon_a64v8_mapping"
                    update_counter(function_arch_extract_mode)
                elif powerpc_altivec_p6_mapping in l:
                    function_arch_extract_mode = "powerpc_altivec_p6_mapping"
                    update_counter(function_arch_extract_mode)
                elif powerpc_altivec_p7_mapping in l:
                    function_arch_extract_mode = "powerpc_altivec_p7_mapping"
                    update_counter(function_arch_extract_mode)
                elif powerpc_altivec_p8_mapping in l:
                    function_arch_extract_mode = "powerpc_altivec_p8_mapping"
                    update_counter(function_arch_extract_mode)
                elif zarch_zvector_13_mapping in l:
                    function_arch_extract_mode = "zarch_zvector_13_mapping"
                    update_counter(function_arch_extract_mode)
                elif zarch_zvector_14_mapping in l:
                    function_arch_extract_mode = "zarch_zvector_14_mapping"
                    update_counter(function_arch_extract_mode)
                elif simde_vectorize_mapping in l:
                    function_arch_extract_mode = "simde_vectorize_mapping"
                    update_counter(function_arch_extract_mode)
                elif simde_convert_vector_mapping in l:
                    function_arch_extract_mode = "simde_convert_vector_mapping"
                    update_counter(function_arch_extract_mode)
                elif simde_vector_subscript_mapping in l:
                    function_arch_extract_mode = "simde_vector_subscript_mapping"
                    update_counter(function_arch_extract_mode)

                if function_arch_extract_mode in function_mappings[function_counter].keys():
                    function_mappings[function_counter][function_arch_extract_mode].append(l)
                else:
                    function_mappings[function_counter][function_arch_extract_mode] = [l]

            function_line += 1

    else:
        if start_function_mapping_string in l:
            start_function_mapping = True 

src.close()

print("Extracted {} functions".format(len(function_mappings)))

dst = open("extracted_mappings.txt", "w")
dst.write(str(function_mappings))
dst.close()


x86mappings = open("x86_mappings.txt", 'w')
armmappings = open("arm_mappings.txt", 'w')
powerpcmappings = open("powerpc_mappings.txt", 'w')

for m in function_mappings:
    x86mappings.write(" ------ " + m["name"] + " ------ \n")
    if "x86_xop_mapping" in m.keys():
        x86mappings.write("x86_xop_mapping:\n")
        x86mappings.write("".join(m["x86_xop_mapping"]))
        x86mappings.write("\n")
    if "x86_sse_mapping" in m.keys():
        x86mappings.write("x86_sse_mapping:\n")
        x86mappings.write("".join(m["x86_sse_mapping"]))
        x86mappings.write("\n")
    if "x86_sse2_mapping" in m.keys():
        x86mappings.write("x86_sse2_mapping:\n")
        x86mappings.write("".join(m["x86_sse2_mapping"]))
        x86mappings.write("\n")
    if "x86_ssse3_mapping" in m.keys():
        x86mappings.write("x86_ssse3_mapping:\n")
        x86mappings.write("".join(m["x86_ssse3_mapping"]))
        x86mappings.write("\n")
    if "x86_sse41_mapping" in m.keys():
        x86mappings.write("x86_sse41_mapping:\n")
        x86mappings.write("".join(m["x86_sse41_mapping"]))
        x86mappings.write("\n")
    if "x86_sse42_mapping" in m.keys():
        x86mappings.write("x86_sse42_mapping:\n")
        x86mappings.write("".join(m["x86_sse42_mapping"]))
        x86mappings.write("\n")
    if "x86_avx2_mapping" in m.keys():
        x86mappings.write("x86_avx2_mapping:\n")
        x86mappings.write("".join(m["x86_avx2_mapping"]))
        x86mappings.write("\n")
    if "x86_avx512vl_mapping" in m.keys():
        x86mappings.write("x86_avx512vl_mapping:\n")
        x86mappings.write("".join(m["x86_avx512vl_mapping"]))
        x86mappings.write("\n")
    if "x86_avx512dq_mapping" in m.keys():
        x86mappings.write("x86_avx512dq_mapping:\n")
        x86mappings.write("".join(m["x86_avx512dq_mapping"]))
        x86mappings.write("\n")
    if "x86_avx512bitalg_mapping" in m.keys():
        x86mappings.write("x86_avx512bitalg_mapping:\n")
        x86mappings.write("".join(m["x86_avx512bitalg_mapping"]))
        x86mappings.write("\n")

    armmappings.write(" ------ " + m["name"] + " ------ \n")
    if "arm_neon_a32v7_mapping" in m.keys():
        armmappings.write("arm_neon_a32v7_mapping:\n")
        armmappings.write("".join(m["arm_neon_a32v7_mapping"]))
        armmappings.write("\n")
    if "arm_neon_a32v7_nn_mapping" in m.keys():
        armmappings.write("arm_neon_a32v7_nn_mapping:\n")
        armmappings.write("".join(m["arm_neon_a32v7_nn_mapping"]))
        armmappings.write("\n")
    if "arm_neon_a32v8_mapping" in m.keys():
        armmappings.write("arm_neon_a32v8_mapping:\n")
        armmappings.write("".join(m["arm_neon_a32v8_mapping"]))
        armmappings.write("\n")
    if "arm_neon_a64v8_mapping" in m.keys():
        armmappings.write("arm_neon_a64v8_mapping:\n")
        armmappings.write("".join(m["arm_neon_a64v8_mapping"]))
        armmappings.write("\n")

    powerpcmappings.write(" ------ " + m["name"] + " ------ \n")

    if "powerpc_altivec_p6_mapping" in m.keys():
        powerpcmappings.write("powerpc_altivec_p6_mapping:\n")
        powerpcmappings.write("".join(m["powerpc_altivec_p6_mapping"]))
        powerpcmappings.write("\n")
    if "powerpc_altivec_p7_mapping" in m.keys():
        powerpcmappings.write("powerpc_altivec_p7_mapping:\n")
        powerpcmappings.write("".join(m["powerpc_altivec_p7_mapping"]))
        powerpcmappings.write("\n")
    if "powerpc_altivec_p8_mapping" in m.keys():
        powerpcmappings.write("powerpc_altivec_p8_mapping:\n")
        powerpcmappings.write("".join(m["powerpc_altivec_p8_mapping"]))
        powerpcmappings.write("\n")
    if "zarch_zvector_13_mapping" in m.keys():
        powerpcmappings.write("zarch_zvector_13_mapping:\n")
        powerpcmappings.write("".join(m["zarch_zvector_13_mapping"]))
        powerpcmappings.write("\n")
    if "zarch_zvector_14_mapping" in m.keys():
        powerpcmappings.write("zarch_zvector_14_mapping:\n")
        powerpcmappings.write("".join(m["zarch_zvector_14_mapping"]))
        powerpcmappings.write("\n")
    
print("Count of extracted functions for architectures")
print(mapping_counter)