#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>

#define SAFE_MALLOC(x) safe_malloc_impl(((x)), __FILE__, __LINE__)

void *safe_malloc_impl(size_t size, const char *file, int line);

#endif
