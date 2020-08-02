#pragma once

#include<map>
#include<string>
#include<cstdint>

#define SECTIONS_COUNT 8;

namespace oxu
{
    enum Sections
    {
        GENERAL_SECTION = 0,
        EDITOR_SECTION = 1,
        METADATA_SECTION = 2,
        DIFFICULTY_SECTION = 3,
        EVENTS_SECTION = 4,
        TIMING_SECTION = 5,
        COLORS_SECTION = 6,
        OBJECTS_SECTION = 7
    };

    extern const std::map<std::string, std::uint8_t> sectionsMap;
}
