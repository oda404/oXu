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

void oxu::MapManager::loadHitObjects(const std::string &mapPath)
{
    std::ifstream infileMap(mapPath);
    std::string line;

    bool shouldReadObjInf = false;

    while(std::getline(infileMap, line))
    {
        if(shouldReadObjInf)
        {
            unsigned int infoArr[3];

            getObjCoreInfo(line, infoArr);

            gcI.hitCircles.emplace_back(infoArr, gcI.playField);
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
