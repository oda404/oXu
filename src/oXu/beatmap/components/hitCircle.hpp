#pragma once

#include<cstdint>

#include<oXu/skin/skin.hpp>
#include<oXu/beatmap/components/hitObject.hpp>
#include<oXu/beatmap/sections/difficulty.hpp>
#include<oXu/utils/vector2.hpp>

namespace oxu
{
    class HitCircle : public HitObject
    {
    public:
        HitCircle(
            const Vector2<float> &position_p,
            const std::uint32_t &hitTime_p,
            const std::uint8_t &type_p,
            const Difficulty &difficulty_p
        );

        void update(const double &delta, const Difficulty &difficulty) override;
        void render(const Skin &skin) override;
        void setErrorMargin(const long double &err, const std::uint32_t &approachRateMs) override;
        bool shouldBeAddedToPool(const std::uint32_t &mapTimeMs) override;
        bool shouldBeRemovedFromPool(const std::uint32_t &mapTimeMs) override;
    };
}
