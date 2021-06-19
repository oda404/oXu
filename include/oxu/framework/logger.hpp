// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<string>
#include<spdlog/spdlog.h>

namespace oxu::framework::logger
{

void init();

#define OXU_LOG_DEBUG(fmt, ...) \
::spdlog::get("oxulogger")->debug( \
    "[DEBUG] " + std::string(fmt), \
    ##__VA_ARGS__ \
)

#define OXU_LOG_INFO(fmt, ...) \
::spdlog::get("oxulogger")->info( \
    "[INFO] " + std::string(fmt), \
    ##__VA_ARGS__ \
)

#define OXU_LOG_WARN(fmt, ...) \
::spdlog::get("oxulogger")->warn( \
    "[WARN] " + std::string(fmt), \
    ##__VA_ARGS__ \
)

#define OXU_LOG_ERROR(fmt, ...) \
::spdlog::get("oxulogger")->error( \
    "[ERROR] " + std::string(fmt), \
    ##__VA_ARGS__ \
)

#define OXU_LOG_DEBUG_EXT(fmt, ...) \
OXU_LOG_DEBUG("[" + std::string(__PRETTY_FUNCTION__) + "] " + fmt, ##__VA_ARGS__)

#define OXU_LOG_INFO_EXT(fmt, ...) \
OXU_LOG_INFO("[" + std::string(__PRETTY_FUNCTION__) + "] " + fmt, ##__VA_ARGS__)

#define OXU_LOG_WARN_EXT(fmt, ...) \
OXU_LOG_WARN("[" + std::string(__PRETTY_FUNCTION__) + "] " + fmt, ##__VA_ARGS__)

#define OXU_LOG_ERROR_EXT(fmt, ...) \
OXU_LOG_ERROR("[" + std::string(__PRETTY_FUNCTION__) + "] " + fmt, ##__VA_ARGS__)

}