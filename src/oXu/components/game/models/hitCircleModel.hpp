#pragma once

#include<cstdint>

#include<oXu/utils/vector2.hpp>

namespace oxu
{
    struct HitCircleModel
    {
        Vector2<float> position;
        uint32_t       hitTime;
        uint16_t       combo;
        float          circleSize;
        float          ARInSeconds;
    };
}
