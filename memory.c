#include "memory.h"
#include "theia_log.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

_Noreturn static void oom_panic(size_t size, const char *file, int line) {
    int err = errno;
    
    THEIA_LOG(LOG_CRITICAL, "OOM Panic at %s:%d | Requested: %zu bytes, Reason: %s", 
              file, line, size, strerror(err));

#ifdef DEBUG
    abort();
#else
    exit(EXIT_FAILURE);
#endif
}

void *safe_malloc_impl(size_t size, const char *file, int line) {
    void *ptr = malloc(size);
    if (!ptr) {
        oom_panic(size, file, line);
    }
    THEIA_LOG(LOG_INFO, "Memory allocated: %zu bytes at %p", size, ptr);
    return ptr;
}
