// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<string>
#include<vector>
#include<map>

#include"../components/game/hitCircle.hpp"
#include"../components/game/playField.hpp"

#include"../utils/timer.hpp"

class HitCircle;

namespace oxu
{
    struct MapInfo
    {
    private:
        MapInfo();

        std::map<std::string, std::string> mapGeneral;
        std::map<std::string, float>       mapDifficulty;
        std::map<std::string, std::string> mapMetadata;

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

        std::vector< HitCircle > hitCircles;

        PlayField                playField;
        Timer                    timer;
        float                    ARInSeconds;

        /* Used to iterate the hit objects more efficiently */
        std::int16_t             hitObjCapTop    = 0;
        std::int16_t             hitObjCapBottom = 0;

        void clear();

        void addGeneralAttr(const std::string &key, const std::string &attr);
        void addDifficultyAttr(const std::string &key, const float &attr);
        void addMetadataAttr(const std::string &key, const std::string &attr);

        inline const std::string &getGeneralAttr(const char *attr) { return mapGeneral.find(attr)->second; }
        inline const float &getDifficultyAttr(const char *attr) { return mapDifficulty.find(attr)->second; }
        inline const std::string &getMetadatAttr(const char *attr) { return mapMetadata.find(attr)->second; }
    };
}
