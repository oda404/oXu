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
        uint16_t approachRateMs;
        float circleSizePx;
    };
}
