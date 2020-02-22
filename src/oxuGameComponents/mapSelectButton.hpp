#pragma once
#include"../oxuGameHandlers/mapManager.hpp"
#include<vector>
#include<iostream>
#include<string>

class MapSelectButton
{
private:
    sf::RectangleShape songRect;
    std::string mapPath;
    sf::Font f;

public:
    MapSelectButton(const std::string mapPath, std::vector<std::string> metaData):
    mapPath(mapPath)
    {
        songRect.setSize({700,150});
        songRect.setOutlineColor(sf::Color(0,0,0,170));
        songRect.setOutlineThickness(5);
        songRect.setFillColor(sf::Color(0,0,0, 125));
        songRect.setPosition({1920 - 700, 400});

        f.loadFromFile("/root/Documents/osuBootleg/textures/coolvetica.ttf");

    }

    sf::RectangleShape getRectangle() const { return songRect; }

    void drawButton(sf::RenderWindow &window)
    {

        window.draw(songRect);

    }
};