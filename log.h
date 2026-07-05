/* Theia Compiler v0.1 - Forensic Logging Interface */
#ifndef LOG_H
#define LOG_H

typedef enum { LOG_INFO, LOG_WARN, LOG_ERROR, LOG_CRITICAL } LogLevel;

void theia_log(LogLevel level, const char *file, int line, const char *fmt, ...);

#define THEIA_LOG(level, ...) theia_log(level, __FILE__, __LINE__, __VA_ARGS__)

#endif
