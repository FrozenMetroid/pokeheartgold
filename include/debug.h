#ifndef DEBUGGING_H
#define DEBUGGING_H

#define LOGGING_ENABLED

#ifdef LOGGING_ENABLED

#define LOG_MESSAGE_MAX_LENGTH 1024

#include <stdarg.h>

#include "constants/charcode.h"
#include "string.h"
#include "../lib/include/nitro/types.h"

void EmulatorVPrintf(const char *text, va_list ap);
int vsnprintf(char *buffer, unsigned int size, const char *fmt, va_list ap);

// Prints to the emulator's standard output, with printf formatting
void EmulatorPrintf(const char *text, ...);

// Prints to the emulator's standard output, with printf formatting, but adds a marker prefix and a newline at the end
void EmulatorLog(const char *text, ...);

#else

#define EmulatorPrintf(...)
#define EmulatorLog(...)

#endif

#endif // DEBUGGING_H