// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"mapManager.hpp"

std::vector<std::string> oxu::MapManager::getMapMetaData(std::string mapPath) const
{
    std::ifstream map(mapPath);
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
    map.close();
    return metaData;
}

std::vector<std::string> oxu::MapManager::getMapDifficulty(std::string mapPath)
{
    std::ifstream map(mapPath);
    std::string line;
    std::vector<std::string> difficulty;
    bool go = false;

    while(std::getline(map,line))
    {
    #ifdef __linux__
        line.erase(line.end() - 1);
    #endif
        if(line == "[Difficulty]")
        {
            go = true;
        }
        
        if((int)line[0] == 0 && go)
            break;
        else if(go && line!="[Difficulty]")
        {
            difficulty.push_back(line.substr(line.find_first_of(':') + 1));
        }
    }

    map.close();
    return difficulty;
}

void oxu::MapManager::loadHitObjects(std::string &path)
{
    bool go = false;

    std::string line;

    std::ifstream file(path);

    while (std::getline(file, line))
    {
    #ifdef __linux__
        line.erase(line.end() - 1);
    #endif
        if (line == "[HitObjects]")
        {
            go = true;
        }
        if (go && line != "[HitObjects]")
        {
            std::string sX = "", sY = "", time = "", sCX = "", sCY = "", sSlides = "", sLength = "";
            int it = 0;
            bool curveTypeCheck = true, curveYCoordsRead = false;
            bool isSlider = false;

            for (unsigned int i = 0; i < line.size(); i++)
            {
                static bool curvePointsGo = false;
                static std::vector<sf::Vector2f> positions;

                if (line[i] != ',' && it == 0)
                {
                    sX += line[i];
                }
                else if (line[i] != ',' && it == 1)
                {
                    sY += line[i];
                }
                else if (line[i] != ',' && it == 2)
                {
                    time += line[i];
                }
                else if (line[i] != ',' && it == 5)
                {
                    if ((line[i] == 'P' || line[i] == 'B' || line[i] == 'L') && curveTypeCheck)
                    {
                        curveType.push_back(line[i]);
                        curvePointsGo = true;
                        curveTypeCheck = false;
                        isSlider = true;
                        if (line[i] != 'L')
                        {
                            int iX, iY;
                            std::istringstream i1(sX);
                            std::istringstream i2(sY);

                            i1 >> iX;
                            i2 >> iY;
                            positions.push_back({ static_cast<float>(iX),static_cast<float>(iY) });
                        }

                    }
                    else if (curveTypeCheck)
                    {
                        curveTypeCheck = false;
                    }
                    else if (curvePointsGo)
                    {
                        bool yDoneReading = false;
                        float iCX, iCY;
                        std::istringstream cX, cY;

                        if (line[i] == ':')
                        {
                            cX = std::istringstream(sCX);
                            cX >> iCX;

                            curveYCoordsRead = true;
                        }
                        else if (line[i] == '|' && line[i - 1] != 'L' && line[i - 1] != 'P' && line[i - 1] != 'B')
                        {
                            sCY = "";
                            sCX = "";
                            curveYCoordsRead = false;
                        }

                        if (!curveYCoordsRead && line[i] != '|')
                            sCX += line[i];
                        else if (curveYCoordsRead && line[i] != ':')
                            sCY += line[i];

                        if (line[i + 1] == '|' || line[i + 1] == ',')
                        {
                            cY = std::istringstream(sCY);
                            cY >> iCY;
                            yDoneReading = true;
                            //y
                        }

                        if (yDoneReading)
                        {
                            positions.push_back({ iCX, iCY });
                            if (line[i + 1] == ',')
                            {
                                curvePointsCoords.push_back(positions);
                                positions.clear();
                            }
                        }
                    }
                }
                else if (line[i] != ',' && it == 6)
                {
                    sSlides += line[i];
                }
                else if (line[i] != ',' && it == 7)
                {
                    sLength += line[i];
                }
                else if (line[i] == ',')
                {
                    curvePointsGo = false;
                    it++;
                }
            }

            if (!isSlider)
            {
                int iX, iY, iTime;

                std::istringstream t(time);
                std::istringstream i1(sX);
                std::istringstream i2(sY);

                t >> iTime;
                i1 >> iX;
                i2 >> iY;

                hitCirclesPositions.push_back({ (float)iX , (float)iY });
                hitCirclesSpawnTimes.push_back(iTime);
            }
            else
            {
                int iX, iY, iTime, iSlides = 0, iLength = 0;

                std::istringstream t(time);
                std::istringstream i1(sX);
                std::istringstream i2(sY);
                std::istringstream isSlides(sSlides);
                std::istringstream isLength(sLength);

                t >> iTime;
                i1 >> iX;
                i2 >> iY;
                isSlides >> iSlides;
                isLength >> iLength;

                slidersPositions.push_back({ (float)iX , (float)iY });
                slidersSpawnTimes.push_back(iTime);
                nOfSlides.push_back(iSlides);
                sliderLengths.push_back(iLength);
            }
        }
    }
    file.close();
}

std::vector<sf::Vector2f> oxu::MapManager::getHitObjectPositions() const { return hitCirclesPositions; }

std::vector<int> oxu::MapManager::gethitObjectSpawnTimes() const { return hitCirclesSpawnTimes; }




std::vector<int> oxu::MapManager::getSlidersSpawnTimes() const { return slidersSpawnTimes; }

std::vector<sf::Vector2f> oxu::MapManager::getSlidersPositions() const { return slidersPositions; }

std::vector<char> oxu::MapManager::getHitObjectCurveType() const { return curveType; }

std::vector<std::vector<sf::Vector2f>> oxu::MapManager::getSliderPointsCoord() const { return curvePointsCoords; }

std::vector<int> oxu::MapManager::getSlides() const { return nOfSlides; }

std::vector<int> oxu::MapManager::getSliderLength() const { return sliderLengths; }

void oxu::MapManager::clearMapInfo()
{
    hitCirclesPositions.clear();
    hitCirclesSpawnTimes.clear();
    curvePointsCoords.clear();
    slidersPositions.clear();
    curveType.clear();
    slidersSpawnTimes.clear();
    nOfSlides.clear();
    sliderLengths.clear();
}
