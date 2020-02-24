#pragma once
#include"../oxuGameHandlers/mapManager.hpp"
#include<vector>
#include<iostream>
#include<string>

class MapSelectButton
{
private:
    sf::RectangleShape mapRect;
    std::string mapPath;
    sf::Font f;

    std::vector<std::string> infoStrings;

public:
    MapSelectButton(const std::string mapPath, std::vector<std::string> metaData):
    mapPath(mapPath)
    {
        mapRect.setSize({700,130});
        mapRect.setOutlineColor(sf::Color(255,255, 255,255));
        mapRect.setOutlineThickness(5);
        mapRect.setFillColor(sf::Color(0,0,0, 125));
        mapRect.setPosition({1920 - 700, 50});

        f.loadFromFile("/root/Documents/osuBootleg/textures/coolvetica.ttf");

        infoStrings.push_back(metaData[0]); //title
        infoStrings.push_back(metaData[2]); //artist
        infoStrings.push_back(metaData[4]); //map creator
        infoStrings.push_back(metaData[5]); //dificulty
    }

    void drawInfo(sf::RenderWindow &window) 
    {
        sf::Text t;
        t.setFont(f);

        float artistRectWidth, creatorRectWidth;

        for(int i = 0; i < infoStrings.size(); ++i)
        {
            switch(i)
            {
            case 0: //song name
                t.setString(infoStrings[i]);
                t.setFillColor(sf::Color::White);
                t.setPosition(mapRect.getPosition().x + 10, mapRect.getPosition().y);
                t.setCharacterSize(35);
                break;
            case 1: //artist
                t.setString( infoStrings[i]);
                t.setFillColor(sf::Color::White);
                t.setPosition(mapRect.getPosition().x + 10, mapRect.getPosition().y + 40);
                t.setCharacterSize(25); 
                artistRectWidth = t.getLocalBounds().width;
                break;
            case 2: //map creator
                t.setString(" | " + infoStrings[i]);
                t.setFillColor(sf::Color::White);
                t.setPosition(mapRect.getPosition().x + 10 + artistRectWidth, mapRect.getPosition().y + 40);
                t.setCharacterSize(25); 
                creatorRectWidth = t.getLocalBounds().width;
                break;
            case 3: //difficulty
                t.setString("[" + infoStrings[i] + "]");
                t.setFillColor(sf::Color::White);
                t.setPosition(mapRect.getPosition().x + 15 + artistRectWidth + creatorRectWidth, mapRect.getPosition().y + 40);
                t.setCharacterSize(25); 
                break;
            }

            window.draw(t);
        }
    }

    void drawButton(sf::RenderWindow &window)
    {
        window.draw(mapRect);
        drawInfo(window);
    }

    void setPosition(sf::Vector2f pos) { mapRect.setPosition(pos); }

    sf::Vector2f getPosition() const { return mapRect.getPosition(); }

    std::string &getMapPath() { return mapPath; }

    void arrangeButtons(std::vector<MapSelectButton> &buttons)
    {
        for(int i = 0; i < buttons.size(); ++i)
        {
            if(i > 0)
                buttons[i].setPosition({buttons[i - 1].getPosition().x , buttons[i - 1].getPosition().y + 150});
        }
    }

    bool checkClick(sf::Vector2i mousePos)
    {
        if(mousePos.x >= mapRect.getPosition().x && mousePos.y >= mapRect.getPosition().y &&
            mousePos.x < mapRect.getPosition().x + mapRect.getLocalBounds().width &&
            mousePos.y < mapRect.getPosition().y + mapRect.getLocalBounds().height )
            {
                return true;
            }
        return false;
    }

    void scrollButtons(std::vector<MapSelectButton> &buttons, float delta)
    {
        if(delta == 1)
        {
            for(auto &button: buttons)
            {
                button.setPosition({button.getPosition().x, button.getPosition().y - 40});
            }
        }
        else if(delta == -1)
        {
            for(auto &button: buttons)
            {
                button.setPosition({button.getPosition().x, button.getPosition().y + 40});
            }
        }
    }
};