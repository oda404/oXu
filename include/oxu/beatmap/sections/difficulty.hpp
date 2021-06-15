#pragma once

#include<cstdint>

namespace oxu
{
    enum class DifficultyField
    {
        HP_DRAIN_RATE = 0,
        CIRCLE_SIZE = 1,
        OVERALL_DIFFICULTY = 2,
        APPROACH_RATE = 3,
        SLIDER_MULTIPLIER = 4,
        SLIDER_TICK_RATE = 5,
        INVALID = 255
    };

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
