#pragma once

#include<map>
#include<string>
#include<cstdint>

#define MAX_TEX_COUNT 4

namespace oxu
{
    enum Tex
    {
        HIT_CIRCLE = 0,
        HIT_CIRCLE_OVERLAY = 1,
        APPROACH_CIRCLE = 2,
        CURSOR_TRAIL = 3,
    };

    extern const std::map<std::string, std::uint8_t> texNamesMap;
}