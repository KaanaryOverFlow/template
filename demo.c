#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define VERBOSE

#ifdef VERBOSE
#define note(...) {printf("\e[1;36m[+] "); printf( __VA_ARGS__); printf("\x1b[0m\n");}
#define info(...) {printf("\e[0;36m[+] "); printf( __VA_ARGS__); printf("\x1b[0m\n");}
#define die(...) {perror(__VA_ARGS__);exit(-1);}
#endif

#ifndef VERBOSE
#define note(...) {}
#define info(...) {}
#define die(...) {puts("[FATAL] \n");fflust(stdout);perror(__VA_ARGS__); exit(-1);}
#endif


int main() {
    note("setting id to 0");
    if(setuid(0)) die("setuid");
    if(setgid(0)) die("setgid");
    note("swtiching root shell")
    system("/system/bin/sh");
    note("dropped from root shell.");
    return 0;
}