#pragma once

#include<string>
#include<cstdint>

namespace oxu
{
    struct General
    {
        std::string audioFilename;
        int audioLeadIn;
        int previewTime;
        int countdown;
        std::string sampleSet;
        float stackLeniency;
        uint8_t mode;
        int letterboxInBreaks;
        int widescreenStoryboard;
    };
}
