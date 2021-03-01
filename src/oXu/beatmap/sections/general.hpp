#pragma once

#include<string>
#include<cstdint>

namespace oxu
{
    enum class GeneralField
    {
        AUDIO_FILENAME = 0,
        AUDIO_LEAD_IN = 1,
        PREVIEW_TIME = 2,
        COUNTDOWN = 3,
        SAMPLE_SET = 4,
        STACK_LENIENCY = 5,
        MODE = 6,
        LETTERBOX_IN_BREAKS = 7,
        WIDESCREEN_STORYBOARD = 8,
        INVALID = 255
    };

    struct General
    {
        std::string audioFilename;
        int audioLeadIn;
        int previewTime;
        int countdown;
        std::string sampleSet;
        float stackLeniency;
        std::uint8_t mode;
        int letterboxInBreaks;
        int widescreenStoryboard;
    };
}
