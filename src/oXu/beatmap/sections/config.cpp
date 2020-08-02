#include"config.hpp"

const std::map<std::string, uint8_t> oxu::sectionsMap = {
    {"[General]\r",      Sections::GENERAL_SECTION},
    {"[Editor]\r",       Sections::EDITOR_SECTION},
    {"[Metadata]\r",     Sections::METADATA_SECTION},
    {"[Difficulty]\r",   Sections::DIFFICULTY_SECTION},
    {"[Events]\r",       Sections::EVENTS_SECTION},
    {"[TimingPoints]\r", Sections::TIMING_SECTION},
    {"[Colours]\r",      Sections::COLORS_SECTION},
    {"[HitObjects]\r",   Sections::OBJECTS_SECTION}
};