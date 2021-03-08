#pragma once

#include<cstdint>
#include<vector>

#include<oXu/beatmap/sections/difficulty.hpp>
#include<oXu/beatmap/components/hitCircle.hpp>
#include<oXu/utils/vector2.hpp>

namespace oxu
{
    enum class SliderCurveType
    {
        LINEAR = 0,
        BEZIER = 1,
        CIRCLE = 2
    };

    struct SliderInfo
    {
        SliderCurveType curve_type;
        std::vector<Vector2<float>> curve_points;
        std::uint16_t slides;
        double length;
        /* edge sounds && edge sets */
    };

    class Slider : public HitCircle
    {
    private:
        std::vector<Vector2<float>> m_curve_points;
        SliderCurveType m_curve_type;
        std::uint16_t m_slides;
        double m_length;

    public:
        Slider(
            const ObjectInfo &obj_info,
            const SliderInfo &slider_info,
            const Difficulty &difficulty
        );

        void update(const double &delta, const Difficulty &difficulty) override;
        void render(const Skin &skin) override;
        void setErrorMargin(const long double &err, const Difficulty &difficulty) override;
        bool shouldAddToPool(const std::uint32_t &mapTimeMs, const std::uint16_t &approach_rate_ms) const override;
        bool shouldRemoveFromPool() const override;
    };
}
