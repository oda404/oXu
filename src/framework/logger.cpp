// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oxu/framework/logger.hpp>

#include<spdlog/sinks/stdout_color_sinks.h>

namespace oxu::framework
{

void logger::init()
{
    auto debugSink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    debugSink->set_level(spdlog::level::off);
    debugSink->set_pattern("%^[%T] [DEBUG] %v%$");

    auto infoSink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    infoSink->set_level(spdlog::level::off);
    infoSink->set_pattern("%^[%T] [INFO] %v%$");

    auto warnSink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    warnSink->set_level(spdlog::level::off);
    warnSink->set_pattern("%^[%T] [WARN] %v%$");

    auto errSink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    errSink->set_level(spdlog::level::off);
    errSink->set_pattern("%^[%T] [ERROR] %v%$");

    spdlog::logger oxuLogger("oxuLogger", {debugSink, infoSink, warnSink, errSink});
    oxuLogger.set_level(spdlog::level::debug);
    spdlog::register_logger(std::make_shared<spdlog::logger>(oxuLogger));
}

}
