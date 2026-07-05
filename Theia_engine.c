#include "memory.h"
#include "jit.h"
#include "theia_log.h"
#include <sys/mman.h>

void execute_raw_logic(uintptr_t phys_addr, const char *asm_code) {
    void *mem = theia_map_phys(phys_addr, 4096);
    
    mprotect(mem, 4096, PROT_READ | PROT_EXEC);
    
    THEIA_LOG(LOG_INFO, "Injecting JIT payload at %p...", mem);
}
