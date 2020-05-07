// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include<experimental/filesystem>
#include<algorithm>

#include"../beatmap/mapInfo.hpp"
#include"../components/textures.hpp"

namespace fs = std::experimental::filesystem;

namespace oxu
{
    class MapManager
    {
    private:
        MapManager();

        /* idk how efficient storing
            every beatmap's name is but fuck it */
        std::vector<std::string> beatMaps;

    public:
        /* Singleton stuff */
        static MapManager &getInstance();

        /* Disable copy-ctor */
        MapManager(const MapManager&) = delete;

        /* Disable move-ctor */
        MapManager(MapManager&&) = delete;

        /* delete assignement operators */
        MapManager& operator=(const MapManager&) = delete;

        MapManager& operator=(MapManager&&) = delete;
        /* ============================================ */


        void loadHitObjects(const int &mapIndex);
        
        void enumBeatMaps();

        void getMapDifficulty(std::ifstream &mapFile);

        void getMapGeneral(std::ifstream &mapFile);

        void getMapMetadata(std::ifstream &mapFile);

        void loadMapInfo(const int &mapIndex);
    };
}
