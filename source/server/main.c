#include "incl.h"
#include "filter.h"
#include "hash.h"

char cmdbuf[144];

int main(int argc, char** argv) {
	if (argc > 1) { }
	puts(">");
	scanf(cmdbuf);
	return 0;
}