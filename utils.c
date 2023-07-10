#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void note(const char *fmt, ...) {
	printf("\033[0;33m[+] ");
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\033[0m");
	printf("\n");
}

void warn(const char *fmt, ...) {
	printf("\033[0;31m[!] ");
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\033[0m");
	printf("\n");
	
}

void info(const char *fmt, ...) {
	printf("\033[47;30m[i] ");
	va_list args;
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\033[0m");
	printf("\n");
	
}


void write_line(const char *fmt, ...) {
	printf("\033[0;32m[?] ");
	va_list args;
    	va_start(args, fmt);
    	vprintf(fmt, args);
    	va_end(args);
	printf("\033[0m");
	for(int i = 0; i < 100; i++)
		printf("\b");
}

void die(const char *fmt) {
	perror(fmt);
	exit(1);
}




