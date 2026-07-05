/* module_loader.c - Dynamic library loading for Theia */
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h> // POSIX standard for dlsym/dlopen

/**
 * Loads a library and returns a handle.
 * Returns NULL on failure.
 */
void *load_module(const char *path) {
    void *handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Theia Error: Cannot load module %s: %s\n", path, dlerror());
    }
    return handle;
}

/**
 * Gets a function pointer from a loaded module.
 */
void *get_function(void *handle, const char *func_name) {
    void *func = dlsym(handle, func_name);
    if (!func) {
        fprintf(stderr, "Theia Error: Cannot find symbol %s\n", func_name);
    }
    return func;
}
