#define LOGGING_ENABLED

#ifdef LOGGING_ENABLED
#include "debug.h"

#include "constants/charcode.h"
#include "string.h"

#define NOCASHGBAIDADDR     0x04FFFA00
#define NOCASHGBAPRINTADDR1 0x04FFFA14 // does not automatically add the newline
#define NOCASHGBAPRINTADDR2 0x04FFFA18 // does automatically add the newline

#define MELONDS_PRINT_MAX_LEN 120

volatile const char **noCashPrint = (volatile const char **)NOCASHGBAPRINTADDR1;

static void EmulatorRawPrint(const char *fmt)
{
    *noCashPrint = fmt;
}

char formattingBuffer[LOG_MESSAGE_MAX_LENGTH];

void EmulatorVPrintf(const char *text, va_list ap)
{
    int res;
    int toprint;
    char *nextPrintStart;

    res = vsnprintf(formattingBuffer, LOG_MESSAGE_MAX_LENGTH, text, ap);
    toprint = res >= LOG_MESSAGE_MAX_LENGTH - 1 ? LOG_MESSAGE_MAX_LENGTH - 1 : res;
    nextPrintStart = formattingBuffer;

    while (toprint > 0) {
        EmulatorRawPrint(nextPrintStart);
        toprint -= MELONDS_PRINT_MAX_LEN;
        nextPrintStart += MELONDS_PRINT_MAX_LEN;
    }
    if (res >= LOG_MESSAGE_MAX_LENGTH - 1) {
        EmulatorRawPrint("\nlog truncated\n");
    }
}
void EmulatorPrintf(const char *text, ...)
{
    va_list args;
    va_start(args, text);
    EmulatorVPrintf(text, args);
    va_end(args);
}

void EmulatorLog(const char *text, ...)
{
    va_list args;
    EmulatorPrintf("[GAME_LOG] ");
    va_start(args, text);
    EmulatorVPrintf(text, args);
    va_end(args);
    EmulatorPrintf("\n");
}
#endif
