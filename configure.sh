if [ -n "$1" ];
then
    C=`locate toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android$1-clang | head -1`
    CXX=`locate toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android$1-clang | tail -1`
    echo "Configuring for arm64"
    echo "C compiler : $C"
    echo "C++ compiler : $CXX"
else
	C=clang
	CXX=clang++
fi



mkdir -p ../build
echo "all: 1" > ../build/Makefile
echo -e "\t@echo Done.\n" >> ../build/Makefile


echo "1:" >> ../build/Makefile
echo -e "\t@$C `pwd`/*.c -static -o pencil" >> ../build/Makefile
echo -e "\t@# adb push pencil /data/local/tmp" >> ../build/Makefile
echo -e "\t@# scp ./pencil root@localhost:/root/\n" >> ../build/Makefile

echo "2:" >> ../build/Makefile
echo -e "\t@$C `pwd`/*.c -DSHARED_LIBRARY -shared -fPIC -o libpencil.so" >> ../build/Makefile
echo -e "\t@# adb push libpencil.so /data/local/tmp" >> ../build/Makefile
echo -e "\t@# scp ./libpencil.so root@localhost:/root/" >> ../build/Makefile

