#ifndef JIT_H
#define JIT_H
#include <stdint.h>

typedef struct {
    void *exec_mem;
    size_t size;
} JITBlock;

JITBlock* jit_compile(const char *asm_code);
void jit_execute(JITBlock *block);
#endif
