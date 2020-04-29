// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<iostream>
#include <experimental/filesystem>

#include"../oxuCore/gameComponents.hpp"
#include"../oxuCore/textures.hpp"


namespace fs = std::experimental::filesystem;

namespace oxu
{
    class MapManager
    {
    private:
        uint32_t numberOfMaps;

        /* idk how efficient storing
            every beatmap's name is but fuck it */
        std::vector<std::string> beatMaps;

        GameComponents &gcI = GameComponents::getInstance();

    public:
        MapManager();

        void loadHitObjects(const std::string &mapPath);
        
        void enumBeatMaps();
    };
}
