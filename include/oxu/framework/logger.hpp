// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<spdlog/spdlog.h>
#include<spdlog/sinks/sink.h>

namespace oxu::framework::logger
{
    void init();

#define SINK_ON(e) spdlog::get("oxuLogger")->sinks()[e - 1]->set_level(e);
#define SINK_OFF(e) spdlog::get("oxuLogger")->sinks()[e - 1]->set_level(spdlog::level::off);

#define OXU_LOG_INFO(form, ...) SINK_ON(spdlog::level::info)\
                    spdlog::get("oxuLogger")->info(form, ##__VA_ARGS__);\
                    SINK_OFF(spdlog::level::info)

#define OXU_LOG_WARN(form, ...) SINK_ON(spdlog::level::warn)\
                    spdlog::get("oxuLogger")->warn(form, ##__VA_ARGS__);\
                    SINK_OFF(spdlog::level::warn)

#define OXU_LOG_ERR(form, ...) SINK_ON(spdlog::level::err)\
                    spdlog::get("oxuLogger")->error(form, ##__VA_ARGS__);\
                    SINK_OFF(spdlog::level::err)

#define OXU_LOG_DEBUG(form, ...) SINK_ON(spdlog::level::debug)\
                    spdlog::get("oxuLogger")->debug(form, ##__VA_ARGS__);\
                    SINK_OFF(spdlog::level::debug)

#define OXU_LOG_INFO_EXT(form, ...) SINK_ON(spdlog::level::info)\
                        spdlog::get("oxuLogger")->info("From [" + std::string(__FILE__) + "] in [" + std::string(__PRETTY_FUNCTION__) + "]: " + form, ##__VA_ARGS__);\
                        SINK_OFF(spdlog::level::info)

#define OXU_LOG_WARN_EXT(form, ...) SINK_ON(spdlog::level::warn)\
                        spdlog::get("oxuLogger")->warn("From [" + std::string(__FILE__) + "] in [" + std::string(__PRETTY_FUNCTION__) + "]: " + form, ##__VA_ARGS__);\
                        SINK_OFF(spdlog::level::warn)

#define OXU_LOG_ERR_EXT(form, ...) SINK_ON(spdlog::level::err)\
                        spdlog::get("oxuLogger")->error("From [" + std::string(__FILE__) + "] in [" + std::string(__PRETTY_FUNCTION__) + "]: " + form, ##__VA_ARGS__);\
                        SINK_OFF(spdlog::level::err)

#define OXU_LOG_DEBUG_EXT(form, ...) SINK_ON(spdlog::level::debug)\
                        spdlog::get("oxuLogger")->debug("From [" + std::string(__FILE__) + "] in [" + std::string(__PRETTY_FUNCTION__) + "]: " + form, ##__VA_ARGS__);\
                        SINK_OFF(spdlog::level::debug)
}