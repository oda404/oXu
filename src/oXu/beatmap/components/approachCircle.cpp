#include"hitCircle.hpp"

namespace oxu
{
    void ApproachCircle::closeIn(const double &delta, const Vector2<float> &origin, const Vector2<float> &targetSize, const float &approachRateMs)
    {
        if(lerpT <= 1.f)
        {
            Vector2<float> newPosition = Vector2<float>::lerp(
                initialSize,
                Vector2<float>(targetSize.x, targetSize.y),
                lerpT
            );

            rect.w = newPosition.x;
            rect.h = newPosition.y;

            rect.x = origin.x - rect.w / 2;
            rect.y = origin.y - rect.h / 2;

            lerpT += delta / (approachRateMs / 1000.0);
        }
    }
}
