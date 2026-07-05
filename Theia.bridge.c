#include "theia_log.h"
#include <stdint.h>
#include <string.h>

/**
 * THEIA OVERLORD CORE
 */

typedef struct {
    void* (*swift_entry)(void*);
    void (*holyc_exec)(void*);
} TrinityTable;

static TrinityTable global_trinity;

void hook_swift_runtime(void* entry_addr) {
    THEIA_LOG(LOG_WARN, "Overlord: Hijacking Swift Runtime at %p", entry_addr);
    global_trinity.swift_entry = (void* (*)(void*))entry_addr;
}

void hook_holyc_soul(void* vm_exec_ptr) {
    THEIA_LOG(LOG_WARN, "Overlord: Injecting HolyC Soul into %p", vm_exec_ptr);
    global_trinity.holyc_exec = (void (*)(void*))vm_exec_ptr;
}


void theia_overlord_execute(int mode, void* data) {
    if (mode == 1) { // Swift Mode
        THEIA_LOG(LOG_INFO, "Executing via Swift-Overlord...");
        global_trinity.swift_entry(data);
    } else { // HolyC Mode
        THEIA_LOG(LOG_INFO, "Executing via HolyC-Overlord...");
        global_trinity.holyc_exec(data);
    }
}
