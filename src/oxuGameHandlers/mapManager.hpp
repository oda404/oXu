#pragma once

#include <vector>
#include <string>
#include<fstream>
#include<boost/filesystem.hpp>

class MapManager
{
private:
    std::vector<boost::filesystem::directory_entry> pathToMaps;
    int numberOfMaps = 0;

public:
    MapManager()
    {
        enumerateMaps();
    }

    void enumerateMaps()
    {
        for (boost::filesystem::directory_entry& x : boost::filesystem::directory_iterator("../songs/"))
        {
            for (boost::filesystem::directory_entry& y : boost::filesystem::directory_iterator(x))
            {
                if(boost::filesystem::extension(y) == ".osu")
                {
                    pathToMaps.push_back(y);
                    ++numberOfMaps;
                }
            }
        }
        std::vector<std::string> getMapInfo;
    }

    std::string getNumberOfMaps() const { return std::to_string(numberOfMaps); }

    std::vector<std::string> getMapMetaData(const int mapNumber) const
    {
        std::ifstream map(boost::filesystem::canonical(pathToMaps[mapNumber]).string());
        std::vector<std::string> metaData;
        std::string line;
        bool go = false;
        
        while(std::getline(map, line))
        {
        #ifdef __linux__
            line.erase(line.end() - 1);
        #endif
            if(line == "[Metadata]")
            {
                go = true;
            }
            
            if((int)line[0] == 0 && go)
                break;
            else if(go && line!="[Metadata]")
            {
                metaData.push_back(line.substr(line.find_first_of(':') + 1));
            }
        }
        
        return metaData;
    }
};