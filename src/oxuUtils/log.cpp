
#include"log.hpp"

void oxu::Log::log(const uint8_t &logLevel, const char *logMessage)
{
    std::cout << logMessages[logLevel] << logMessage << std::endl;
}

void oxu::Log::log(const uint8_t &logLevel, const int &logMessage)
{
    std::cout << logMessages[logLevel] << logMessage << std::endl;
}