// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include<oxu/framework/logger.hpp>
#include<spdlog/sinks/stdout_color_sinks.h>

namespace oxu::framework::logger
{

void init()
{
    std::vector<spdlog::sink_ptr> log_sinks;
    log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

    log_sinks[0]->set_pattern("%^%v%$");

    auto logger = std::make_shared<spdlog::logger>(
        "oxulogger", 
        begin(log_sinks), 
        end(log_sinks)
    );
    spdlog::register_logger(logger);
    logger->set_level(spdlog::level::trace);
    logger->flush_on(spdlog::level::trace);
}

}
