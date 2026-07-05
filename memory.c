#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdnoreturn.h>

_Noreturn static void oom_panic(size_t size, const char *file, int line) {
    int err = errno;
    fprintf(stderr, "FATAL: Memory allocation failed at %s:%d\n", file, line);
    fprintf(stderr, "Requested: %zu bytes, Reason: %s\n", size, strerror(err));
#ifdef DEBUG
    abort();
#else
    exit(EXIT_FAILURE);
#endif
}

void *safe_malloc_impl(size_t size, const char *file, int line) {
    void *ptr = malloc(size);
    if (!ptr) oom_panic(size, file, line);
    return ptr;
}
