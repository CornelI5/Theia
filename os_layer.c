// os_layer.h
void *os_allocate_executable_memory(size_t size);
void os_set_memory_executable(void *ptr, size_t size);

// os_layer.c (Linux/Mac example)
#include <sys/mman.h>
void *os_allocate_executable_memory(size_t size) {
    return mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC, 
                MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}
