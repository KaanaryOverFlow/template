all: clean demo
	@echo "DONE"

clean:
	echo > demo
	rm demo

demo: demo.c
	aarch64-linux-android33-clang -static demo.c -o demo
	@adb push ./demo /data/local/tmp/