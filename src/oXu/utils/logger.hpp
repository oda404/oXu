// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<spdlog/spdlog.h>
#include<spdlog/sinks/stdout_color_sinks.h>

namespace oxu::Logger
{
    void init();
    
    #define LOG_INFO  spdlog::info
    #define LOG_WARN  spdlog::warn
    #define LOG_ERR   spdlog::error
    #define LOG_DEBUG spdlog::debug
}