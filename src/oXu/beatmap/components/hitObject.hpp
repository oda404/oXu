#pragma once

#include<cstdint>

#include<SDL2/SDL_rect.h>

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
        ApproachCircle approachCircle;
        Vector2<float> position;
        std::uint32_t hitTime;
        uint8_t type;

    public:
        HitObject(
            const Vector2<float> &position_p,
            const std::uint32_t &hitTime_p,
            const std::uint8_t &type_p
        );

        virtual void update(const double &delta, const Difficulty &difficulty) = 0;
        virtual void render(SDL_Renderer *targetRenderer, Skin *currentSkin) = 0;
        virtual void setErrorMargin(const long double &err, const std::uint32_t &approachRateMs) = 0;
        virtual bool shouldBeAddedToPool(const std::uint32_t &mapTimeMs) = 0;
        virtual bool shouldBeRemovedFromPool(const std::uint32_t &mapTimeMs) = 0;
        double getApproachCircleDonePercentage();
        /* unlike getType() this returns the obj type (HIT_CIRCLE || SLIDER || SPINNER) */
        uint8_t getObjType();
        const Vector2<float> &getPosition();
        const std::uint32_t &getHitTime();
        const uint8_t &getType();
    };
}