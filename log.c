#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

void theia_log(LogLevel level, const char *file, int line, const char *fmt, ...) {
    const char *labels[] = {"INFO", "WARN", "ERROR", "CRIT"};
    
    time_t now = time(NULL);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

    fprintf(stderr, "[%s] [%s] %s:%d | ", timestamp, labels[level], file, line);
    
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    
    fprintf(stderr, "\n");
}
