#pragma once

#include<spdlog/spdlog.h>
#include<spdlog/sinks/stdout_color_sinks.h>

#include<memory>

namespace oxu
{
    class Logger
    {
    private:
        static std::shared_ptr<spdlog::logger> logger;

    public:
        static void init();

        static std::shared_ptr<spdlog::logger> &getLogger();
    };

    #define LOG_INFO Logger::getLogger()->info
    #define LOG_WARN Logger::getLogger()->warn
    #define LOG_ERR  Logger::getLogger()->error
}