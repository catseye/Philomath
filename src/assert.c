#include <stdlib.h>
#include <stdio.h>

#include "assert.h"

void assert(int v, const char *s) {
    if (!v) {
        fprintf(stdout, "Assertion failed: '%s'\n", s);
        exit(1);
    }
}
