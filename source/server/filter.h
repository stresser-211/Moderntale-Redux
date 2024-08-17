#ifndef FILTER_H
#define FILTER_H

#include "incl.h"

char operators[21] = {'@', '[', ']', '(', ')', '&', '|', '^', '!', '?', '%', '~', '/', '\\', '+', ':', ';', '=', '#', '<', '>'};

const char* sanitariser(const char string[420]) { //remove the
	return string;
}

#endif // FILTER_H