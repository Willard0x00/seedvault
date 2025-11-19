#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

void print_h(int n) {
	printf("%x %x %x %x\n", n & 0xff, n >> 8 & 0xff, n >> 16 & 0xff, n >> 24 & 0xff);
}

void print_b(int n) {
	for (int i = 0; i < sizeof(int) * 8; ++i) {
		(i % 8 == 0 && i != 0) ? printf(" ") : 0;
		(n & 0x80000000) ? printf("1") : printf("0");
		n = n << 1;
	}
	printf("\n");
}

#endif