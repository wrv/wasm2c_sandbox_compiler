llvm_path=clang 

## WASI-SDK included clang
wasiclang_SOURCE_DIR='../../../wasi-sdk-14.0'
wasm_llvm=$wasiclang_SOURCE_DIR/bin/clang

## WASM2C Folder
wasm2c_folder=../../wasm2c
bin_folder=../../bin

curfile="wasm_simd_intrinsics_lib"

echo "[X] Build $curfile.c"
echo " - [X] Compiling to WASM with wasi-clang"
$wasm_llvm --sysroot ${wasiclang_SOURCE_DIR}/share/wasi-sysroot/ \
                            -O3                         \
                            -Wl,--export-all            \
                            -Wl,--no-entry              \
                            -Wl,--growable-table        \
                            -Wl,--stack-first           \
                            -Wl,-z,stack-size=1048576   \
                            -msimd128                   \
                            -o $curfile.wasm            \
                            $curfile.c                  \
                            wasm2c_sandbox_wrapper.c
if [ $? -eq 0 ]; then
    #$wasm_llvm $curfile.c -o $curfile.wasm --target=wasm32-unknown-unknown-wasm -c -msimd128 # -mllvm -debug
    echo " - [X] Running wasm2wat"
    rm $curfile.wasm2c.wat 2> /dev/null
    $bin_folder/wasm2wat $curfile.wasm > $curfile.wasm2c.wat
    echo " - [X] Running wasm2c RLbox"
    rm $curfile.wasm2c.c 2> /dev/null
    rm $curfile.wasm2c.h 2> /dev/null
    #echo $bin_folder/wasm2c $curfile.wasm -o $curfile.wasm2c.c
    $bin_folder/wasm2c $curfile.wasm -vv -o $curfile.wasm2c.c &> $curfile.wasm2c.verbose_log.txt
    if [ $? -eq 0 ]; then
        echo " - [X] Building Program"
        $llvm_path -I$wasm2c_folder -o $curfile.wasm2c.out -mavx \
                    $curfile.main.c                  \
                    $curfile.wasm2c.c                \
                    $wasm2c_folder/wasm-rt-impl.c    \
                    $wasm2c_folder/wasm-rt-os-unix.c \
                    $wasm2c_folder/wasm-rt-os-win.c  \
                    $wasm2c_folder/wasm-rt-wasi.c
        if [ $? -eq 0 ]; then
            echo " - [X] Running Output"
            #echo $w2c_runner ./$curfile.wasm2c.so
            ./$curfile.wasm2c.out 4
            if [ $? -eq 0 ]; then
                echo "All done!"
            else 
                echo " - [ERROR] Issue running Output"
                echo "Command: $curfile.wasm2c.out 4"
            fi
        else 
            echo " - [ERROR] Error building shared library for $curfile"
            echo "Command: $llvm_path -I$wasm2c_folder -o $curfile.wasm2c.out $curfile.main.c $curfile.wasm2c.c $wasm2c_folder/wasm-rt-impl.c $wasm2c_folder/wasm-rt-os-unix.c $wasm2c_folder/wasm-rt-os-win.c  $wasm2c_folder/wasm-rt-wasi.c"
        fi
    else 
        echo " - [ERROR] Error with wasm2c - check log: $curfile.wasm2c.verbose_log.txt"
        echo "   Command: $bin_folder/wasm2c $curfile.wasm -vv -o $curfile.wasm2c.c "
    fi
else 
    echo " - [ERROR] Error compiling to WASM with wasi-clang"
    echo "Command: $wasm_llvm --sysroot ${wasiclang_SOURCE_DIR}/share/wasi-sysroot/ -O3 -Wl,--export-all -Wl,--no-entry -Wl,--growable-table -Wl,--stack-first -Wl,-z,stack-size=1048576 -msimd128 -o $curfile.wasm $curfile.c"
fi

# clang -I../../wasm2c -o wasm_simd_intrinsics_lib.wasm2c.out wasm_simd_intrinsics_lib.main.c wasm_simd_intrinsics_lib.wasm2c.c ../../wasm2c/wasm-rt-impl.c ../../wasm2c/wasm-rt-os-unix.c ../../wasm2c/wasm-rt-os-win.c ../../wasm2c/wasm-rt-wasi.c

# clang -I../../wasm2c -o wasm_simd_intrinsics_lib.wasm2c.out wasm_simd_intrinsics_lib.main.c wasm_simd_intrinsics_lib.wasm2c.c ../../wasm2c/wasm-rt-impl.c ../../wasm2c/wasm-rt-os-unix.c ../../wasm2c/wasm-rt-os-win.c ../../wasm2c/wasm-rt-wasi.c -mavx