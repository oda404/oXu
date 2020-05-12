#pragma once

#include<string>
#include<vector>
#include<map>

#include"../components/game/hitCircle.hpp"
#include"../components/game/playField.hpp"

#include"../utils/timer.hpp"

namespace oxu
{
    struct MapInfo
    {
    private:
        MapInfo();

    public:
        /* ========== Singleton stuff ================== */
        static MapInfo &getInstance();

        /* Disable copy-ctor */
        MapInfo(const MapInfo&)            = delete;

        /* Disable move-ctor */
        MapInfo(MapInfo&&)                 = delete;

        /* Delete assignement operators */
        MapInfo& operator=(const MapInfo&) = delete;

        MapInfo& operator=(MapInfo&&)      = delete;
        /* ============================================== */

        std::map<std::string, std::string> mapGeneral;
        std::map<std::string, float>       mapDifficulty;
        std::map<std::string, std::string> mapMetadata;

        std::vector< HitCircle >           hitCircles;

        PlayField                          playField;
        Timer                              timer;
        float                              ARInSeconds;

        /* Used to iterate the hit objects more efficiently */
        std::int16_t                       hitObjCapTop    = 0;
        std::int16_t                       hitObjCapBottom = 0;

        void clear();
    };
}
