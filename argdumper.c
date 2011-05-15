/* trivial diagnostic tool to test mcfifo.exe's arg passing */

#include <stdio.h>

int main(int argc, char **argv) {
    int i;
    for (i = 0; i < argc; ++i) {
        fprintf(stderr, "arg %d: %s\n", i, argv[i]);
    }
    return 0;
}
