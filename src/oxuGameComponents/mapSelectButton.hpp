// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<string>
#include<fstream>

namespace oxu
{
    class MapSelectButton
    {
    private:
        sf::RectangleShape mapRect;
        std::string mapPath;
        sf::Font f;

        std::vector<std::string> infoStrings;

    public:
        MapSelectButton(const std::string &mapPath, const std::vector<std::string> metaData);

        void drawInfo(sf::RenderWindow &window);

        void drawButton(sf::RenderWindow &window);

        void setPosition(sf::Vector2f pos);

        sf::Vector2f getPosition() const;

        std::string &getMapPath();

        std::string getSongPath();

        void arrangeButtons(std::vector<MapSelectButton> &buttons);

        bool checkClick(sf::Vector2i mousePos);

        void scrollButtons(std::vector<MapSelectButton> &buttons, float delta);
    };
}
