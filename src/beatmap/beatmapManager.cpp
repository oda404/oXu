// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"beatmapManager.hpp"

bool isBitOn(const uint8_t &number, const uint8_t &bit)
{
    if( (number & ( 1 << bit ) ) >> bit ) 
    {
        return true;
    }

    return false;
}

std::vector<std::string> split(const std::string &str, const char &splitChar)
{
    std::vector<std::string> result;
    unsigned int lastPos = 0;
    unsigned int i = 0;

    for(; i < str.size(); ++i)
    {
        if(str[i] == splitChar)
        {
            result.emplace_back(str.substr(lastPos, i - lastPos));
            lastPos = i + 1;
        }
    }
    
    result.emplace_back(str.substr(lastPos, i - lastPos + 1));

    return result;
}

/* Returns the flags for the specified object */
uint8_t getObjCoreInfo(const std::string &line, uint infoArr[4])
{
    std::vector<std::string> splitInfo = split(line, ',');

    infoArr[0] = std::stoi(splitInfo[0]); // X
    infoArr[1] = std::stoi(splitInfo[1]); // Y
    infoArr[2] = std::stoi(splitInfo[2]); // hit time

    return std::stoi(splitInfo[3]); // flags
}

void getSliderExtraInfo(const std::string &line, std::vector<oxu::Vector2<float>> &controlPoints, int &repeats, double &length, uint8_t type)
{
    std::vector<std::string> splitInfo = split(line, ',');

    std::vector<std::string> splitControlPoints = split(splitInfo[5], '|');

    for(std::size_t i = 1; i < splitControlPoints.size(); ++i)
    {
        std::vector<std::string> cp = split(splitControlPoints[i], ':');
        controlPoints.emplace_back(std::stoi(cp[0]), std::stoi(cp[1]));
    }

    switch(splitInfo[5][0]) // first character of the 5th sub string
    {
        case 'L':
            type = oxu::SliderType::Linear;
            break;

        case 'P':
            type = oxu::SliderType::Circle;
            break;

        case 'B':
            type = oxu::SliderType::Bezier;
            break;
    }

    repeats = std::stoi(splitInfo[6]);
    length = std::stod(splitInfo[7]);
}

namespace oxu
{
    void BeatmapManager::updateCombo(const uint8_t &flags)
    {
        isBitOn(flags, 2) ? combo = 1 : ++combo;
    }

    void BeatmapManager::addHitObject(const std::string &line, const PlayField &playField)
    {
        /*
        The core info array contains:
        [0] = posX,
        [1] = posY
        [2] = hit time
        [3] = combo
        */
        unsigned int coreInfoArr[4];

        /* Parse the object line */
        uint8_t flags = getObjCoreInfo(line, coreInfoArr);

        updateCombo(flags);

        coreInfoArr[3] = combo;

        /* Check the type of the object */

        if(isBitOn(flags, 0)) // it's a hit circle
        {
            hitObjectsInfo.addHitCircle(coreInfoArr, playField, beatmapInfo);
        }
        else if(isBitOn(flags, 1)) // it's a slider
        {
            std::vector<Vector2<float>> controlPoints;

            /* Add the initial x y position */
            controlPoints.emplace_back(coreInfoArr[0], coreInfoArr[1]);

            int repeats;
            double length;
            uint8_t type;

            getSliderExtraInfo(line, controlPoints, repeats, length, type);

            hitObjectsInfo.addSlider(coreInfoArr, controlPoints, repeats, length, type, playField, beatmapInfo);
        }
        else if(isBitOn(flags, 3)) // it's a spinner
        {

        }
    }

    /* Populate the hitCircles vector in the MapInfo singleton */
    void BeatmapManager::loadHitObjects(const int &songI, const int &mapI)
    {
        PlayField playField;

        std::ifstream infileMap(beatmaps[songI].second[mapI]);
        std::string line;

        bool shouldReadObjInf = false;

        while(std::getline(infileMap, line))
        {
            if(shouldReadObjInf)
            {
                addHitObject(line, playField);
            }
            else if(line == "[HitObjects]\r")
            {
                shouldReadObjInf = true;
            }
        }

        infileMap.close();
    }

    /* Go through every map in the songs folder
    *  and store it's path in a vector to be accessed
    *  with an index
    */
    void BeatmapManager::enumBeatMaps()
    {
        beatmaps.clear();

        const char *mapFolderPath = "songs/";
        for(auto &p: fs::directory_iterator(mapFolderPath))
        {
            if(fs::is_directory(p))
            {
                std::pair<std::string, std::vector<std::string>> beatMap;
                beatMap.first = p.path();

                LOG_DEBUG("Loaded Song: {0}", p.path().filename().c_str());

                for(auto &file: fs::directory_iterator(p))
                {
                    if(file.path().extension() == ".osu")
                        beatMap.second.emplace_back(file.path());
                }
                beatmaps.emplace_back(beatMap);
            }
        }
    }

    /* ================== Difficulty ============================= */
    void BeatmapManager::getMapDifficulty(std::ifstream &mapFile)
    {
        std::string line;
        bool go = false;

        while(std::getline(mapFile, line))
        {
            /* if it's still reading the difficulty section
            and encounters a blank line (new section) break */
            if(line == "\r" && go)
                break;

            if(go)
            {
                std::string keyValue  = line.substr(0, line.find_first_of(':'));
                float       diffValue = stof(line.substr(line.find_first_of(':') + 1));

                beatmapInfo.addDifficultyAttr(keyValue, diffValue);
            }
            else if(line == "[Difficulty]\r")
            {
                go = true;
            }
        }

        float AR = beatmapInfo.getDifficultyAttr("ApproachRate");
        beatmapInfo.ARInSeconds = AR <= 5 ? 1800 - AR * 120 : 1200 - (AR - 5) * 150;
        beatmapInfo.ARInSeconds /= 1000;
    }

    /* ====================== [General] ===================== */
    void BeatmapManager::getMapGeneral(std::ifstream &mapFile)
    {
        std::string   line;
        bool          go = false;

        while(std::getline(mapFile, line))
        {
            if(line == "\r" && go)
                break;
            
            if(go)
            {
                std::string keyValue  = line.substr(0, line.find_first_of(':'));
                std::string diffValue = line.substr(line.find_first_of(':') + 1);

                /* Remove all spaces from string */
                diffValue.erase(std::remove_if(diffValue.begin(), diffValue.end(), isspace));
                diffValue.erase(diffValue.find_last_of('\r'));

                beatmapInfo.addGeneralAttr(keyValue, diffValue);
            }
            else if(line == "[General]\r")
            {
                go = true;
            }
        }
    }

    /* ======================== [Metadata] ====================== */
    void BeatmapManager::getMapMetadata(std::ifstream &mapFile)
    {
        std::string line;
        bool go = false;

        while(std::getline(mapFile, line))
        {
            if(line == "\r" && go)
                break;

            if(go)
            {
                std::string keyValue  = line.substr(0, line.find_first_of(':'));
                std::string diffValue = line.substr(line.find_first_of(':') + 1);

                /* Remove all spaces from string */
                diffValue.erase(std::remove_if(diffValue.begin(), diffValue.end(), isspace));

                beatmapInfo.addMetadataAttr(keyValue, diffValue);
            }
            else if(line == "[Metadata]\r")
            {
                go = true;
            }
        }
    }

    /* Load the General, Metadata and Difficulty sections
    *  of the beatmap at the specified index
    */
    void BeatmapManager::loadMapInfo(const int &songI, const int &mapI)
    {
        beatmapInfo.clear();
        std::ifstream infileMap(beatmaps[songI].second[mapI]);

        getMapGeneral(infileMap);
        getMapMetadata(infileMap);
        getMapDifficulty(infileMap);
    }

    std::string &BeatmapManager::getSongPath(const int &index)
    {
        return beatmaps[index].first;
    }

    BeatmapInfo &BeatmapManager::getBeatmapInfo()
    {
        return beatmapInfo;
    }

    HitObjectsInfo &BeatmapManager::getObjectsInfo()
    {
        return hitObjectsInfo;
    }
}
