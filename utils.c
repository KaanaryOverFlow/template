#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sched.h>
#include <pthread.h>
#include <sys/mman.h>

#include "utils.h"

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


void hexdump(const void* data, size_t size) {
	char ascii[17];
	size_t i, j;
	ascii[16] = '\0';
	for (i = 0; i < size; ++i) {
		printf("%02X ", ((unsigned char*)data)[i]);
		if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			ascii[i % 16] = ((unsigned char*)data)[i];
		} else {
			ascii[i % 16] = '.';
		}
		if ((i+1) % 8 == 0 || i+1 == size) {
			printf(" ");
			if ((i+1) % 16 == 0) {
				printf("|  %s \n", ascii);
			} else if (i+1 == size) {
				ascii[(i+1) % 16] = '\0';
				if ((i+1) % 16 <= 8) {
					printf(" ");
				}
				for (j = (i+1) % 16; j < 16; ++j) {
					printf("   ");
				}
				printf("|  %s \n", ascii);
			}
		}
	}
}

void pin_cpu(int num) {
	cpu_set_t  mask;
	CPU_ZERO(&mask);
	CPU_SET(num, &mask);
	if ( sched_setaffinity(0, sizeof(mask), &mask)) die("pinning cpu");
}

unsigned long hammer_flag = 0;

void *_hammer_thread_busy_function(void *x) {
	int core = (unsigned long)x & 0xffffffff;
	pin_cpu(core);
	while(!hammer_flag);
	return NULL;
}

pthread_t hammer_tid;

void *_hammer_thread_function(void *x) {
	pthread_t *ids = (pthread_t *)x;
	int core = *(int *)ids;
	pin_cpu(core);
	note("Hammering on %lu cpu", core);
	
	FOR(10000) {
		if(pthread_create(&ids[i], NULL, _hammer_thread_busy_function, (void *)core) < 0) die("pthread failed to create busy loop");
	}

	while(!hammer_flag);
	return NULL;
}

void hammer(int core) {
	note("getting hammer on core %d", core);
	pthread_t *ids = mmap(NULL, 10000 * 8, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ids == MAP_FAILED) die("hammer map failed");
	*(int *)ids = core;

	if ( pthread_create(&hammer_tid, NULL, _hammer_thread_function, (void *)ids) < 0) die("pthread failed to create hammer");
	note("Hammered. ");
}

