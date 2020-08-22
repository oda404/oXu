#pragma once

#include<cstdint>
#include<vector>

#include<SDL2/SDL_rect.h>

#include<oXu/beatmap/sections/difficulty.hpp>
#include<oXu/utils/vector2.hpp>

namespace oxu
{
    struct HitCircleParams
    {
        Vector2<float> position;
        uint32_t hitTime;
        /* this is not the same "type" as in the beatmap file, 
        it's only the type of the object (CIRCLE || SLIDER || SPINNER) */
        uint8_t type;
    };

    struct SliderParams
    {
        char type;
        std::vector<Vector2<float>> controlPoints;
        int repeats;
        double expectedLength;
    };

    class HitObject
    {
    private:
        Vector2<float> position;
        SDL_Rect HCRect;
        SDL_Rect ACRect;
        Vector2<float> ACInitialSize;
        float ACT = 0.0f;
        uint32_t localSpawnTime;
        uint32_t localHitTime;
        
        uint8_t type;

        SliderParams *sliderParams = NULL;

    public:
        HitObject(
            const Vector2<float> &position_p, 
            const uint32_t &hitTime_p,
            uint8_t type_p,
            const Difficulty &difficulty
        );

        HitObject(
            const Vector2<float> &position_p,
            const uint32_t &hitTime_p,
            uint8_t type_p,
            const SliderParams &sliderParams_p,
            const Difficulty &difficulty
        );

        ~HitObject();

        void setErrorMargin(const double &err, const uint32_t &arMs);

        const uint32_t &getLocalHitTime();

        const uint32_t &getLocalSpawnTime();

        const SDL_Rect *getHCRect();

        const SDL_Rect *getACRect();

        bool shouldBeAddedToPool(const uint32_t &ellapsedMapTime);

        bool shouldBeRemovedFromPool(const uint32_t &ellapsedMapTime);

        void approachCircle(const float &delta, const float &AR);
    };
}