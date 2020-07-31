#pragma once

#include<cstdint>

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_rect.h>

#include<oXu/core/scaling.hpp>
#include<oXu/beatmap/sections/difficulty.hpp>
#include<oXu/beatmap/components/playField.hpp>
#include<oXu/utils/vector2.hpp>
#include<oXu/utils/logger.hpp>

namespace oxu
{
    class HitObject
    {
    private:
        SDL_Rect HCRect;
        SDL_Rect ACRect;

        Vector2<float> ACInitialSize;
        float ACT = 0.0f;

        Vector2<float> position;
        uint32_t hitTime;
        uint32_t spawnTime;
        uint8_t type;

    public:
        HitObject(
            const Vector2<float> &position_p, 
            const uint32_t &hitTime_p,
            uint8_t type_p,
            const PlayField &playField,
            const Difficulty &difficulty
        );

        int errorMargin = 0;

        const uint32_t &getHitTime();

        const uint32_t &getSpawnTime();

        const SDL_Rect *getHCRect();

        const SDL_Rect *getACRect();

        void render(SDL_Renderer *targetRenderer);

        bool shouldBeAddedToPool(const uint32_t &time);

        bool shouldBeRemovedFromPool(const uint32_t &time);

        void approachCircle(const float &delta, const float &AR);
        
    };
}