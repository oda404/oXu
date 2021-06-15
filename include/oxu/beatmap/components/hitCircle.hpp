#pragma once

#include<cstdint>

#include<oxu/skin/skin.hpp>
#include<oxu/beatmap/components/hitObject.hpp>
#include<oxu/beatmap/sections/difficulty.hpp>
#include<oxu/utils/vector2.hpp>

namespace oxu
{
    class HitCircle : public HitObject
    {   
    public:
        HitCircle(
            const ObjectInfo &obj_info,
            const Difficulty &difficulty
        );

        void update(const double &delta, const Difficulty &difficulty) override;
        void render(const Skin &skin) override;
        void setErrorMargin(const long double &err, const Difficulty &difficulty) override;
        bool shouldAddToPool(const std::uint32_t &map_time_ms, const std::uint16_t &approach_rate_ms) const override;
        bool shouldRemoveFromPool() const override;
    };
}
