#include "registry.h"
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_MODULES 64
static Module *modules[MAX_MODULES];
static int module_count = 0;

Module *registry_load(const char *name, const char *path) {
    // Cek dulu udah ada apa belum
    for (int i = 0; i < module_count; i++) {
        if (strcmp(modules[i]->name, name) == 0) {
            modules[i]->ref_count++;
            return modules[i];
        }
    }

    void *handle = dlopen(path, RTLD_LAZY);
    if (!handle) return NULL;

    Module *mod = malloc(sizeof(Module));
    mod->handle = handle;
    mod->name = strdup(name);
    mod->ref_count = 1;

    modules[module_count++] = mod;
    return mod;
}

bool registry_unload(const char *name) {
    for (int i = 0; i < module_count; i++) {
        if (strcmp(modules[i]->name, name) == 0) {
            modules[i]->ref_count--;
            if (modules[i]->ref_count == 0) {
                dlclose(modules[i]->handle);
                free(modules[i]->name);
                free(modules[i]);
                modules[i] = modules[--module_count];
                return true;
            }
            return true;
        }
    }
    return false;
}

void *registry_get_symbol(Module *mod, const char *func_name) {
    return dlsym(mod->handle, func_name);
}
