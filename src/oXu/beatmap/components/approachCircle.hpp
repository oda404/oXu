#pragma once

#include<oXu/utils/vector2.hpp>

namespace oxu
{
    struct ApproachCircle
    {
    public:
        Vector2<float> size;
        Vector2<float> position;
        Vector2<float> initialSize = {0.f, 0.f};
        double lerpT = 0.0;

        void closeIn(const double &delta, const Vector2<float> &origin, const Vector2<float> &targetSize, const float &approachRateMs);
    };
}