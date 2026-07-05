/* module_registry.h */
typedef struct {
    void *handle;
    char *name;
    int reference_count; 
} Module;

void unload_module(Module *mod) {
    if (--mod->reference_count == 0) {
        dlclose(mod->handle);
    }
}
