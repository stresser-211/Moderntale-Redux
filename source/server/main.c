#include "incl.h"
#include "utility.h"
#include "hash.h"

char cmdbuf[144];

int main(int argc, char** argv) {
	logfile = fopen("../stacktrace.log", "a");
	if (argc > 1) { }
	for (;;) {
		THROW();
	}
	CATCH();

	return 0;
}