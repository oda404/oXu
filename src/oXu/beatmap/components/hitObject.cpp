#include"hitObject.hpp"

namespace oxu
{
    HitObject::HitObject(
        const Vector2<float> &position_p,
        const std::uint32_t &hitTime_p,
        const std::uint8_t &type_p,
        const Difficulty &difficulty_p
    ): mx_originPosition(position_p), mx_hitTime(hitTime_p), mx_spawnTime(mx_hitTime - difficulty_p.approachRateMs), mx_type(type_p)
    {
        mx_size.x = difficulty_p.circleSizePx;
        mx_size.y = mx_size.x;

        mx_position = mx_originPosition - mx_size / 2;

        mx_approachCircle.size = mx_size * 2.75f;
        mx_approachCircle.position = position_p - mx_approachCircle.size / 2;
        mx_approachCircle.initialSize = mx_approachCircle.size;
    }

    double HitObject::getApproachCircleDonePercentage()
    {
        return mx_approachCircle.lerpT * 100.0;
    }

    const Vector2<float> &HitObject::getPosition()
    {
        return mx_position;
    }

    const std::uint32_t &HitObject::getHitTime()
    {
        return mx_hitTime;
    }

    const uint8_t &HitObject::getType()
    {
        return mx_type;
    }
}
