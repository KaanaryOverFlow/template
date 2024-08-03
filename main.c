#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "utils.h"
#include "memory.h"

struct {
	int fd;	
} *ed;

void setup() {
	note("\t\t###################################################");
	note("\t\t# 盲目人間はこの世界で色がありませんに思うか？    #");
	note("\t\t# この人は思うと道がありません。人間は思うるです。#");
	note("\t\t###################################################");
	note("\t\t				    Zedeleyici.1337");
	ed = mmap(NULL, 4096 * 2, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ed == MAP_FAILED) die("inital map of setup");


}

void default_app() {
	in();
	out();
}

void sec_main(char *param) {
	if (!param) {
		default_app();
	} else {
		die("invalid parameter");
	}

}


int main(int argc, char *argv[]) {
	in();
	setup();
	sec_main(argv[1]);
	out();
	return 0;
}
