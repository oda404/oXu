#pragma once

#include<map>
#include<string>
#include<cstdint>

#define GENERAL_SECTION 0
#define EDITOR_SECTION 1
#define METADATA_SECTION 2
#define DIFFICULTY_SECTION 3
#define EVENTS_SECTION 4
#define TIMING_SECTION 5
#define COLORS_SECTION 6
#define OBJECTS_SECTION 7

namespace oxu
{
    extern std::map<std::string, std::uint8_t> sectionsMap;
}
