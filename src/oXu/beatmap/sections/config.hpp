#pragma once

#include<map>
#include<string>
#include<cstdint>

#define SECTIONS_COUNT 8;

namespace oxu
{
    enum Sections
    {
        GENERAL = 0,
        EDITOR = 1,
        METADATA = 2,
        DIFFICULTY = 3,
        EVENTS = 4,
        TIMING = 5,
        COLORS = 6,
        OBJECTS = 7
    };

    extern const std::map<std::string, std::uint8_t> sectionsMap;
}
