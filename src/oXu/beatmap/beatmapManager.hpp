// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<experimental/filesystem>
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdint>

#include<oXu/beatmap/beatmapInfo.hpp>
#include<oXu/beatmap/hitObjectsInfo.hpp>

#include<oXu/components/game/sliderTypes.hpp>
#include<oXu/components/game/playField.hpp>
#include<oXu/components/game/models/hitCircldeModel.hpp>

namespace fs = std::experimental::filesystem;

namespace oxu
{
    class BeatmapManager
    {
    private:
        std::vector<std::pair<std::string, std::vector<std::string>>> beatmaps;
        uint16_t combo = 1;

        BeatmapInfo    beatmapInfo;
        HitObjectsInfo hitObjectsInfo;

        HitCircleModel HCModel;
        
        void addHitObject(const std::string &line, const PlayField &playField);

        uint8_t setObjCoreInfo(const std::string &line);
        
    public:
        void loadHitObjects(const int &songI, const int &mapI);
        
        void enumBeatMaps();

        void getMapDifficulty(std::ifstream &mapFile);

        void getMapGeneral(std::ifstream &mapFile);

        void getMapMetadata(std::ifstream &mapFile);

        void loadMapInfo(const int &songI, const int &mapI);

        std::string &getSongPath(const int &index);

        BeatmapInfo &getBeatmapInfo();

        HitObjectsInfo &getObjectsInfo();
    };
}
