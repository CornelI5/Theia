/*
 * Theia Compiler v0.1 - Module Registry
 * Licensed under MIT License
 */
#ifndef REGISTRY_H
#define REGISTRY_H

#include <stdbool.h>

typedef struct {
    void *handle;
    char *name;
    int ref_count;
} Module;

bool registry_init(void);
Module *registry_load(const char *name, const char *path);
bool registry_unload(const char *name);
void *registry_get_symbol(Module *mod, const char *func_name);
void registry_cleanup(void);

#endif
