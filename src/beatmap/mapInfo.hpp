#pragma once

#include<vector>
#include<map>
#include<string>

#include"../components/game/hitCircle.hpp"
#include"../utils/timer.hpp"
#include"../components/game/playField.hpp"

namespace oxu
{
    struct MapInfo
    {
    private:
        MapInfo();

    public:
        /* Singleton stuff */
        static MapInfo &getInstance();

        /* Disable copy-ctor */
        MapInfo(const MapInfo&) = delete;

        /* Disable move-ctor */
        MapInfo(MapInfo&&) = delete;

        /* Delete assignement operators */
        MapInfo& operator=(const MapInfo&) = delete;

        MapInfo& operator=(MapInfo&&) = delete;
        /* ============================================== */

        PlayField                    playField;
        Timer                        mapTimer;
        std::vector<HitCircle>       hitCircles;
        std::map<std::string, float> mapDifficulty;
        float                        ARInSeconds;

        void clearMap();
    };
}