/*
 * Theia Runtime Core 
 */
#include "theia_log.h"
#include "memory.h"
#include "jit.h"
#include <stdio.h>

typedef struct {
    bool is_initialized;
} TheiaRuntime;

static TheiaRuntime global_runtime = { .is_initialized = false };

void theia_init() {

    THEIA_LOG(LOG_INFO, "Bootstrapping Theia Runtime...");
    
    THEIA_LOG(LOG_INFO, "Memory subsystem & Physical Mapping ready.");
    
    THEIA_LOG(LOG_INFO, "JIT & Swift bridge initialized.");
    
    global_runtime.is_initialized = true;
    THEIA_LOG(LOG_INFO, "Theia Runtime is now LIVE.");
}

int main(int argc, char **argv) {
    theia_init();


    return 0;
}
