#include <stdio.h>
#include <stdlib.h>

// External libraries
#include "log.h"

// Configuration
#define DEBUG_MODE true
#define DEBUG_OUTPUT_FILE ".\\output.txt"


int main() { 
#if DEBUG_MODE
    clock_t tic = clock();
    FILE *fp = fopen(DEBUG_OUTPUT_FILE, "w+");
    log_add_fp(fp, LOG_DEBUG);
#endif

    printf("Hello world!\n\n");

#if DEBUG_MODE
    clock_t toc = clock();
    log_debug("Elapsed: %f seconds", (double)(toc - tic) / CLOCKS_PER_SEC);
    fclose(fp);
#endif

    return EXIT_SUCCESS;
}
