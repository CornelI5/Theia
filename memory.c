#include "memory.h"
#include "theia_log.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

void *theia_map_phys(uintptr_t phys_addr, size_t size) {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        THEIA_LOG(LOG_CRITICAL, "Failed to open /dev/mem. Need root privileges.");
        exit(EXIT_FAILURE);
    }

    size_t page_size = sysconf(_SC_PAGESIZE);
    uintptr_t offset = phys_addr % page_size;
    uintptr_t aligned_addr = phys_addr - offset;

    void *ptr = mmap(NULL, size + offset, PROT_READ | PROT_WRITE, MAP_SHARED, fd, aligned_addr);
    close(fd);

    if (ptr == MAP_FAILED) {
        THEIA_LOG(LOG_ERROR, "Mapping 0x%lx failed", phys_addr);
        return NULL;
    }

    THEIA_LOG(LOG_INFO, "Mapped 0x%lx to virtual address %p", phys_addr, ptr + offset);
    return (void *)((uintptr_t)ptr + offset);
}

void theia_unmap_phys(void *virt_addr, size_t size) {
    munmap(virt_addr, size); 
}
