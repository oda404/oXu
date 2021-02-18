#include"config.hpp"

const std::map<std::string, uint8_t> oxu::sectionsMap = {
    {"[General]\r",      Sections::GENERAL},
    {"[Editor]\r",       Sections::EDITOR},
    {"[Metadata]\r",     Sections::METADATA},
    {"[Difficulty]\r",   Sections::DIFFICULTY},
    {"[Events]\r",       Sections::EVENTS},
    {"[TimingPoints]\r", Sections::TIMING},
    {"[Colours]\r",      Sections::COLORS},
    {"[HitObjects]\r",   Sections::OBJECTS}
};