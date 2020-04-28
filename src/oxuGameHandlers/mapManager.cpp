// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"mapManager.hpp"

oxu::MapManager::MapManager() { }

void oxu::MapManager::loadHitObjects(const std::string &mapPath)
{
    std::ifstream infileMap(mapPath);
    std::string line;

    bool shouldReadObjInf = false;

    while(std::getline(infileMap, line))
    {
        if(shouldReadObjInf)
        {
            int x, y;
            uint32_t spawnTime;

        }
        else if(line == "[HitObjects]\r")
        {
            shouldReadObjInf = true;
        }
    }

    infileMap.close();
}

void oxu::MapManager::enumBeatMaps()
{
    beatMaps.clear();
    numberOfMaps = 0;

    const char *mapFolderPath = "songs/";
    for(auto &p: fs::directory_iterator(mapFolderPath))
    {
        beatMaps.push_back(p.path());
        ++numberOfMaps;
    }
}

void getObjCoreInfo(const std::string &line, int &d_x, int &d_y, uint32_t &d_time)
{
    for(char c: line)
    {

    }
}