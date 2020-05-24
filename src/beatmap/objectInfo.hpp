#pragma once

#include<vector>
#include<cstdint>

#include"../components/game/hitCircle.hpp"
#include"../utils/timer.hpp"

namespace oxu
{
    struct ObjectInfo
    {
    private:
        std::vector< HitCircle > hitCircles;

    public:
        Timer   timer;
        /* Used to iterate the hit objects more efficiently */
        int16_t HCTopCap = 0;
        int16_t HCBotCap = 0;

        void clear();

        void addHitCircle(unsigned int infoArr[4], PlayField &playField, MapInfo &mapInfo);

        HitCircle &getHCAt(const unsigned int &index);
    };
}