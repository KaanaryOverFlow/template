if [ -n "$1" ];
then
    C=`locate toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android$1-clang | head -1`
    CXX=`locate toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android$1-clang | tail -1`
    echo "Configuring for arm64"
    echo "C compiler : $C"
    echo "C++ compiler : $CXX"
    cmake -D CMAKE_C_COMPILER=$C -D CMAKE_CXX_COMPILER=$CXX -B ../build -S .
else
    cmake -B ../build -S .
fi