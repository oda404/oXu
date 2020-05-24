// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<experimental/filesystem>
#include<algorithm>
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdint>

#include"mapInfo.hpp"
#include"objectInfo.hpp"

#include"../components/game/playField.hpp"

namespace fs = std::experimental::filesystem;

namespace oxu
{
    class MapManager
    {
    private:
        std::vector<std::pair<std::string, std::vector<std::string>>> beatmaps;
        int combo = 1;

        MapInfo beatmapInfo;
        ObjectInfo objectInfo;

        /* Updates the current combo based on the 2nd bit flag */
        void updateCombo(const uint8_t &flags);
        
    public:
        void loadHitObjects(const int &songI, const int &mapI);
        
        void enumBeatMaps();

        void getMapDifficulty(std::ifstream &mapFile);

        void getMapGeneral(std::ifstream &mapFile);

        void getMapMetadata(std::ifstream &mapFile);

        void loadMapInfo(const int &songI, const int &mapI);

        std::string getSongPath(const int &index);

        MapInfo &getCurrentBeatmapInfo();

        ObjectInfo &getCurrentObjectInfo();

    };
}
