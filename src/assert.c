#include <stdlib.h>
#include <stdio.h>

#include "assert.h"

void assert(int v) {
    if (!v) {
        fprintf(stdout, "Assertion failed\n");
        exit(1);
    }
}
