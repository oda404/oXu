// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SFML/Graphics.hpp>
#include <vector>
#include <string>
#include<sstream>
#include<fstream>
#include<boost/filesystem.hpp>
#include"../oxuGameComponents/mapSelectButton.hpp"
namespace oxu
{
    class MapManager
    {
    private:

        std::vector<MapSelectButton> *mapSelectionButtons;

        //info about the map's hit circles===================================
        std::vector<sf::Vector2f> hitCirclesPositions;
        std::vector<int> hitCirclesSpawnTimes;
        //===================================================================
        //info about the map's sliders========================================
        std::vector<std::vector<sf::Vector2f>> curvePointsCoords;
        std::vector<sf::Vector2f> slidersPositions;
        std::vector<char> curveType;
        std::vector<int> slidersSpawnTimes; 
        std::vector<int> nOfSlides;
        std::vector<int> sliderLengths;
        //===================================================================

    public:
        MapManager(std::vector<MapSelectButton> *buttonsPtr);

        void enumerateMaps();

        int getNumberOfMaps() const { return mapSelectionButtons->size(); }

        std::vector<std::string> getMapMetaData(std::string mapPath) const;

        std::vector<std::string> getMapDifficulty(std::string mapPath);

        void loadHitObjects(std::string &path);

        std::vector<sf::Vector2f> getHitObjectPositions() const;

        std::vector<int> gethitObjectSpawnTimes() const;

        std::vector<int> getSlidersSpawnTimes() const;

        std::vector<sf::Vector2f> getSlidersPositions() const;
        
        std::vector<char> getHitObjectCurveType() const;

        std::vector<std::vector<sf::Vector2f>> getSliderPointsCoord() const;

        std::vector<int> getSlides() const;

        std::vector<int> getSliderLength() const;

        void clearMapInfo();
    };
}
