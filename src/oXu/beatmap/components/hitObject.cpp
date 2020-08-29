#include"hitObject.hpp"

namespace oxu
{
    static uint8_t parseObjectType(const uint8_t &type)
    {
        if( type  & (1 << 0) )
        {
            return 0;
        }
        else if( type & (1 << 1) )
        {
            return 1;
        }

        return 2;
    }

    HitObject::HitObject(
        const Vector2<float> &position_p,
        const std::uint32_t &hitTime_p,
        const std::uint8_t &type_p
    ): position(position_p), hitTime(hitTime_p), type(type_p)
    {

    }

    double HitObject::getApproachCircleDonePercentage()
    {
        return approachCircle.lerpT * 100.0;
    }

    uint8_t HitObject::getObjType()
    {
        return parseObjectType(type);
    }

    const Vector2<float> &HitObject::getPosition()
    {
        return position;
    }

    const std::uint32_t &HitObject::getHitTime()
    {
        return hitTime;
    }

    const uint8_t &HitObject::getType()
    {
        return type;
    }
}
