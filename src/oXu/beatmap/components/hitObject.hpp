#pragma once

#include<cstdint>

#include<oXu/beatmap/components/approachCircle.hpp>
#include<oXu/beatmap/sections/difficulty.hpp>
#include<oXu/skin/skin.hpp>
#include<oXu/utils/vector2.hpp>

namespace oxu
{
    /* Base class for all the other hitObjects */
    class HitObject
    {
    protected:
        ApproachCircle mx_approachCircle;
        Vector2<float> mx_position;
        Vector2<float> mx_size;
        Vector2<float> mx_originPosition;
        std::uint32_t mx_hitTime;
        std::uint32_t mx_spawnTime;
        std::uint8_t mx_type;

    public:
        HitObject(
            const Vector2<float> &position_p,
            const std::uint32_t &hitTime_p,
            const std::uint8_t &type_p,
            const Difficulty &difficulty_p
        );

        virtual void update(const double &delta, const Difficulty &difficulty) = 0;
        virtual void render(const Skin &skin) = 0;
        virtual void setErrorMargin(const long double &err, const std::uint32_t &approachRateMs) = 0;
        virtual bool shouldBeAddedToPool(const std::uint32_t &mapTimeMs) = 0;
        virtual bool shouldBeRemovedFromPool(const std::uint32_t &mapTimeMs) = 0;
        double getApproachCircleDonePercentage();
        const Vector2<float> &getPosition();
        const std::uint32_t &getHitTime();
        const uint8_t &getType();
    };
}
