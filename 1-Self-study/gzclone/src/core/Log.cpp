#include "core/Log.h"

#include <cstdio>
#include <cstdarg>

namespace
{
    void LogInfoV(const char* fmt, std::va_list args)
    {
        std::vprintf(fmt, args);
        std::printf("\n");
        std::fflush(stdout);
    }
}

void LogInfo(const char* fmt, ...)
{
    std::va_list args;
    va_start(args, fmt);
    LogInfoV(fmt, args);
    va_end(args);
}
