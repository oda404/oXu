#pragma once

#include<cstdint>

namespace oxu
{
    struct TimingPoint
    {
        uint32_t time;
        float beatLength;
        int meter;
        int sampleSet;
        int sampleIndex;
        int volume;
        bool uninherited;
        uint8_t effects;
    };
}
