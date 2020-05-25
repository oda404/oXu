// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"logger.hpp"

std::shared_ptr<spdlog::logger> oxu::Logger::logger;

void oxu::Logger::init()
{
    spdlog::set_pattern("%^[%T] %v%$");
    logger = spdlog::stdout_color_mt("oxuLogger");
    logger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger> &oxu::Logger::getLogger()
{
    return logger;
}
