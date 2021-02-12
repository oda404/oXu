#include"hitCircle.hpp"

namespace oxu
{
    bool ApproachCircle::closeIn(
        const double &delta, 
        const Vector2<float> &origin, 
        const Vector2<float> &targetSize, 
        const float &approachRateMs
    )
    {
        if(lerpT <= 1.f)
        {
            size = Vector2<float>::lerp(
                initialSize,
                targetSize,
                lerpT
            );
            position = origin - size / 2;
            lerpT += delta / (approachRateMs / 1000.0);
            return false;
        }

        return true;
    }
}
