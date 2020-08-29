#pragma once

#include<cstdint>

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_rect.h>

#include<oXu/skin/skin.hpp>
#include<oXu/beatmap/components/hitObject.hpp>
#include<oXu/beatmap/sections/difficulty.hpp>
#include<oXu/utils/vector2.hpp>

namespace oxu
{
    class HitCircle : public HitObject
    {
    private:
        SDL_Rect rect;
        std::uint32_t spawnTime;

    public:
        HitCircle(
            const Vector2<float> &position_p,
            const std::uint32_t &hitTime_p,
            const std::uint8_t &type_p,
            const Difficulty &difficulty_p
        );

        void update(const double &delta, const Difficulty &difficulty) override;
        void render(SDL_Renderer *targetRenderer, Skin *currentSkin) override;
        void setErrorMargin(const long double &err, const std::uint32_t &approachRateMs) override;
        bool shouldBeAddedToPool(const std::uint32_t &mapTimeMs) override;
        bool shouldBeRemovedFromPool(const std::uint32_t &mapTimeMs) override;
    };
}
