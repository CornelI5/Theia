/*
 * Theia Compiler v0.1 - Memory Management
 * Licensed under MIT License
 */
#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>


void *safe_malloc_impl(size_t size, const char *file, int line);


#define SAFE_MALLOC(size) safe_malloc_impl((size), __FILE__, __LINE__)

#endif
