#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

void *safe_malloc_impl(size_t size, const char *file, int line);
#define SAFE_MALLOC(s) safe_malloc_impl((s), __FILE__, __LINE__)

void *theia_map_phys(uintptr_t phys_addr, size_t size);
void theia_unmap_phys(void *virt_addr, size_t size);

#endif
