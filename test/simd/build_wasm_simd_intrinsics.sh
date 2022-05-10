## This is LLVM15 - most up to date version
llvm_path=clang 

## WASI-SDK included clang
wasm_llvm='/mnt/d/research/wasmsimd/wasi-sdk-14.0/bin/clang'
wasiclang_SOURCE_DIR='/mnt/d/research/wasmsimd/wasi-sdk-14.0'

## WASM2C Folder
wasm2c_folder=../../wasm2c
bin_folder=../../bin


curfile="wasm_simd_intrinsics"
echo "[X] Build $curfile.c"
# if we add -O3 to the command below then it'll transform multiple_arrays2 into its SIMD version as well
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
                            $curfile.c
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
        echo " - [X] Building shared library"
        $llvm_path -I$wasm2c_folder -shared -fPIC -o $curfile.wasm2c.so \
                    $curfile.wasm2c.c                \
                    $wasm2c_folder/wasm-rt-impl.c    \
                    $wasm2c_folder/wasm-rt-os-unix.c \
                    $wasm2c_folder/wasm-rt-os-win.c  \
                    $wasm2c_folder/wasm-rt-runner.c  \
                    $wasm2c_folder/wasm-rt-wasi.c
        if [ $? -eq 0 ]; then
            echo " - [X] Running with wasm2c-runner"
            #echo $w2c_runner ./$curfile.wasm2c.so
            $bin_folder/wasm2c-runner ./$curfile.wasm2c.so
            if [ $? -eq 0 ]; then
                echo "All done!"
            else 
                echo " - [ERROR] Issue running wasm2c_runner"
                echo "Command: $w2c_runner ./$curfile.wasm2c.so"
            fi
        else 
            echo " - [ERROR] Error building shared library for $curfile"
            echo "Command: $llvm_path -I$wasm2c_folder -shared -fPIC -o $curfile.wasm2c.so $curfile.wasm2c.c $wasm2c_folder/wasm-rt-impl.c $wasm2c_folder/wasm-rt-os-unix.c $wasm2c_folder/wasm-rt-os-win.c $wasm2c_folder/wasm-rt-runner.c $wasm2c_folder/wasm-rt-wasi.c"
        fi
    else 
        echo " - [ERROR] Error with wasm2c - check log: $curfile.wasm2c.verbose_log.txt"
        echo "   Command: $bin_folder/wasm2c $curfile.wasm -vv -o $curfile.wasm2c.c "
    fi
else 
    echo " - [ERROR] Error compiling to WASM with wasi-clang"
    echo "Command: $wasm_llvm --sysroot ${wasiclang_SOURCE_DIR}/share/wasi-sysroot/ -O3 -Wl,--export-all -Wl,--no-entry -Wl,--growable-table -Wl,--stack-first -Wl,-z,stack-size=1048576 -msimd128 -o $curfile.wasm $curfile.c"
fi