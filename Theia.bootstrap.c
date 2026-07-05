#include "theia_log.h"
#include "memory.h"
#include "registry.h" 

extern void swift_runtime_init(); 

extern void holyc_vm_init();

void theia_bootstrap() {
    THEIA_LOG(LOG_INFO, "--- Starting Theia Trinity Boot ---");

    THEIA_LOG(LOG_INFO, "C-Layer: Core initialized.");

    THEIA_LOG(LOG_INFO, "Swift-Layer: Hooking into Swift runtime...");
    swift_runtime_init(); 

    THEIA_LOG(LOG_INFO, "HolyC-Layer: Summoning HolyC VM...");
    holyc_vm_init();
  
    THEIA_LOG(LOG_INFO, "Trinity Handshake complete. Theia is unified.");
}
