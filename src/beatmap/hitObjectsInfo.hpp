#pragma once

#include<vector>
#include<cstdint>

#include"../components/game/hitCircle.hpp"
#include"../components/game/slider.hpp"
#include"../utils/timer.hpp"

namespace oxu
{
    struct HitObjectsInfo
    {
    private:
        std::vector< HitCircle > hitCircles;
        std::vector< Slider >    sliders;

    public:
        Timer   timer;
        /* Used to iterate the hit objects more efficiently */
        int16_t HCTopCap = 0;
        int16_t HCBotCap = 0;

        void clear();

        void addHitCircle(unsigned int infoArr[4], PlayField &playField, BeatmapInfo &mapInfo);

        HitCircle &getHCAt(const unsigned int &index);
    };
}