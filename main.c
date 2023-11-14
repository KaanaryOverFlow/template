#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "utils.h"

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

	ed->fd = open("/dev/dri/card0", O_RDWR);
	if (ed->fd < 0) die("open Failed");

}

int main() {
	in();
	setup();
	out();
	return 0;
}
