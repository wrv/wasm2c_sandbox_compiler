llvm_path=clang 

## WASI-SDK included clang
wasiclang_SOURCE_DIR='../../../../wasi-sdk-14.0'
wasm_llvm=$wasiclang_SOURCE_DIR/bin/clang

## WASM2C Folder
wasm2c_folder=../../../wasm2c
bin_folder=../../../bin


curfile="wasm_simd_intrinsics_lib"

param=37
if [[ $1 ]]
  then
    echo "Using supplied parameter $1"
    param=$1
else 
    echo "Using default parameter $param"
fi



echo "[X] Build $curfile.c"
echo " - [X] Compiling to WASM with wasi-clang"
# compile with -O0 for now
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
    echo " - [X] Running wasm2wat"
    # clean up previous file
    rm $curfile.wasm2c.wat 2> /dev/null

    $bin_folder/wasm2wat $curfile.wasm > $curfile.wasm2c.wat
    # read -p "Press enter to continue"
    echo " - [X] Running wasm2c"
    # clean up previous files
    rm $curfile.wasm2c.c 2> /dev/null
    rm $curfile.wasm2c.h 2> /dev/null

    $bin_folder/wasm2c $curfile.wasm -vv -o $curfile.wasm2c.c &> $curfile.wasm2c.verbose_log.txt
    if [ $? -eq 0 ]; then
        # read -p "Press enter to continue"
        # Replace this line before building in $curfile.wasm2c.c
        # v128 w2c_l20 = 0, w2c_l24 = 0, w2c_l25 = 0, w2c_l26 = 0, w2c_l27 = 0, w2c_l28 = 0, w2c_l29 = 0, w2c_l30 = 0, 
        #    w2c_l33 = 0;
        # v128 w2c_l20, w2c_l24, w2c_l25, w2c_l26, w2c_l27, w2c_l28, w2c_l29, w2c_l30, w2c_l33;

        echo " - [X] Building wasm2c output"
        $llvm_path -I$wasm2c_folder -o $curfile.wasm2c.out -mavx \
                    $curfile.main.c                  \
                    $curfile.wasm2c.c                \
                    $wasm2c_folder/wasm-rt-impl.c    \
                    $wasm2c_folder/wasm-rt-os-unix.c \
                    $wasm2c_folder/wasm-rt-os-win.c  \
                    $wasm2c_folder/wasm-rt-wasi.c
        if [ $? -eq 0 ]; then
            # read -p "Press enter to continue"
            echo " - [X] Saving objdump of binary"
            objdump -d $curfile.wasm2c.out > $curfile.wasm2c.out.objdump.txt

            echo " - [X] Running Output with param $param"
            echo ./$curfile.wasm2c.out $param
            ./$curfile.wasm2c.out $param
            if [ $? -eq 0 ]; then
                echo " "
            else 
                echo " - [ERROR] Issue running Output"
                echo "Command: $curfile.wasm2c.out $param"
            fi
        else 
            echo " - [ERROR] Error building shared library for $curfile"
            echo "Command: $llvm_path -I$wasm2c_folder -o $curfile.wasm2c.out -mavx $curfile.main.c $curfile.wasm2c.c $wasm2c_folder/wasm-rt-impl.c $wasm2c_folder/wasm-rt-os-unix.c $wasm2c_folder/wasm-rt-os-win.c $wasm2c_folder/wasm-rt-wasi.c"
        fi
    else 
        echo " - [ERROR] Error with wasm2c - check log: ./$curfile.wasm2c.verbose_log.txt"
        echo "   Command: $bin_folder/wasm2c $curfile.wasm -vv -o $curfile.wasm2c.c "
    fi
else 
    echo " - [ERROR] Error compiling to WASM with wasi-clang"
    echo "Command: $wasm_llvm --sysroot ${wasiclang_SOURCE_DIR}/share/wasi-sysroot/ -O3 -Wl,--export-all -Wl,--no-entry -Wl,--growable-table -Wl,--stack-first -Wl,-z,stack-size=1048576 -msimd128 -o $curfile.wasm $curfile.c wasm2c_sandbox_wrapper.c"
fi