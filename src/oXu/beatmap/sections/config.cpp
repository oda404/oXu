#include"config.hpp"

std::map<std::string, uint8_t> oxu::sectionsMap = {
    {"[General]\r",      GENERAL_SECTION},
    {"[Editor]\r",       EDITOR_SECTION},
    {"[Metadata]\r",     METADATA_SECTION},
    {"[Difficulty]\r",   DIFFICULTY_SECTION},
    {"[Events]\r",       EVENTS_SECTION},
    {"[TimingPoints]\r", TIMING_SECTION},
    {"[Colours]\r",      COLORS_SECTION},
    {"[HitObjects]\r",   OBJECTS_SECTION}
};