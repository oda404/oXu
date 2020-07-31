#pragma once

#include<cstdint>

namespace oxu
{
    struct Difficulty
    {
        float HPDrainRate;
        float circleSize;
        float overallDifficulty;
        float approachRate;
        float sliderMultiplier;
        float sliderTickRate;
        uint32_t approachRateMs;
        uint32_t circleSizePx;
    };
}
