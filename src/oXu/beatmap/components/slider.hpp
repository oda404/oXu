#pragma once

#include<cstdint>
#include<vector>

#include<oXu/beatmap/sections/difficulty.hpp>
#include<oXu/beatmap/components/hitCircle.hpp>
#include<oXu/utils/vector2.hpp>

namespace oxu
{
    class Slider : public HitCircle
    {
    private:
        std::vector<Vector2<float>> controlPoints;
        char sType;
        int repeats;
        double expectedLength;

    public:
        Slider(
            const Vector2<float> &position_p,
            const std::uint32_t &hitTime_p,
            const std::uint8_t &type_p,
            const std::vector<Vector2<float>> &controlPoints_p,
            const char &sType_p,
            const int &repeats_p,
            const double &expectedLength_p,
            const Difficulty &difficulty_p
        );

        void update(const double &delta, const Difficulty &difficulty) override;
        void render(const Skin &skin) override;
        void setErrorMargin(const long double &err, const std::uint32_t &approachRateMs) override;
        bool shouldBeAddedToPool(const std::uint32_t &mapTimeMs) override;
        bool shouldBeRemovedFromPool(const std::uint32_t &mapTimeMs) override;
    };
}
