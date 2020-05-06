// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"mapManager.hpp"

/* because fuck that dogshit stoi function
    never works*/
uint parseIntFromStr(const std::string &str)
{
	uint integer = 0;

	for(int i = 0; i < str.size(); ++i)
		if((int)str[i] >= 48 && (int)str[i] <= 57)
			integer = integer * 10 + (int)str[i] - 48;

	return integer;
}

void getObjCoreInfo(const std::string &line, uint infoArr[3])
{
    std::string buff;
    uint8_t     commaN = 0;
    uint8_t     commaPos = 0;

    for(const char &c: line)
    {
        if(c != ',')
            buff += c;
        else
        {
            if(commaN < 3)
            {
                infoArr[commaN++] = parseIntFromStr(buff.substr(commaPos));
                commaPos = buff.size();
            }
            else
                break;
        }      
    }
}

oxu::MapManager::MapManager() { }

oxu::MapManager &oxu::MapManager::getInstance()
{
    static MapManager instance;
    return instance;
}

void oxu::MapManager::loadHitObjects(const int &mapIndex)
{
    MapInfo &mapInfoI = MapInfo::getInstance();

    std::ifstream infileMap(beatMaps[mapIndex]);
    std::string line;

    bool shouldReadObjInf = false;

    while(std::getline(infileMap, line))
    {
        if(shouldReadObjInf)
        {
            unsigned int infoArr[3];

            getObjCoreInfo(line, infoArr);

            mapInfoI.hitCircles.emplace_back(infoArr, mapInfoI.playField);
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

    const char *mapFolderPath = "songs/";
    for(auto &p: fs::directory_iterator(mapFolderPath))
    {
        beatMaps.push_back(p.path());
    }
}

void oxu::MapManager::getMapDifficulty(const int &mapIndex)
{
    MapInfo &mapInfoI = MapInfo::getInstance();

    std::ifstream infileMap(beatMaps[mapIndex]);
    std::string line;
    bool go = false;

    while(std::getline(infileMap, line))
    {
        /* if it's still reading the difficulty section
        and encounters a blank line (new section) break */
        if(line == "\r" && go)
            break;

        if(go)
        {
            std::string keyValue = line.substr(0, line.find_first_of(':'));
            float       diffValue = stof(line.substr(line.find_first_of(':') + 1));

            mapInfoI.mapDifficulty.emplace(keyValue, diffValue);

            /* transform the value into seconds */
            if(keyValue == "ApproachRate")
            {
                if(diffValue <= 5)
                    mapInfoI.ARInSeconds = 1800 - diffValue * 120;
                else
                    mapInfoI.ARInSeconds = 1200 - (diffValue - 5) * 150;

                mapInfoI.ARInSeconds /= 1000;
            }
        }
        else if(line == "[Difficulty]\r")
        {
            go = true;
        }
    }
}
