#pragma once

#include<iostream>
#include<cstdint>

namespace oxu
{
    class Log
    {
    private:
        const char *logMessages[3] = 
        {
            "[LOG] ",
            "[WARNING] ",
            "[ERROR] ",
        };

    public:
        void log(const uint8_t &logLevel, const char *logMessage);

        void log(const uint8_t &logLevel, const int &logMessage);

        enum logLevels
        {
            LOG     = 0,
            WARNING = 1,
            ERROR   = 2,
        };
    };
}