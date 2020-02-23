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

    std::vector<std::string> infoStrings;

public:
    MapSelectButton(const std::string mapPath, std::vector<std::string> metaData):
    mapPath(mapPath)
    {
        songRect.setSize({700,150});
        songRect.setOutlineColor(sf::Color(255,255, 255,255));
        songRect.setOutlineThickness(5);
        songRect.setFillColor(sf::Color(0,0,0, 125));
        songRect.setPosition({1920 - 700, 50});

        f.loadFromFile("/root/Documents/osuBootleg/textures/coolvetica.ttf");

        infoStrings.push_back(metaData[0]); //title
        infoStrings.push_back(metaData[2]); //artist
        infoStrings.push_back(metaData[4]); //map creator
        infoStrings.push_back(metaData[5]); //dificulty

    }

    sf::RectangleShape getRectangle() const { return songRect; }

    void drawInfo(sf::RenderWindow &window) 
    {
        sf::Text t;
        t.setFont(f);

        for(int i = 0; i < infoStrings.size(); ++i)
        {
            switch(i)
            {
            case 0: //song name
                t.setString(infoStrings[i]);
                t.setFillColor(sf::Color::White);
                t.setPosition(songRect.getPosition().x + 20, songRect.getPosition().y);
                t.setCharacterSize(45);
                break;
            case 1: //artist
                t.setString(infoStrings[i]);
                t.setFillColor(sf::Color::White);
                t.setPosition(songRect.getPosition().x + 20, songRect.getPosition().y + 50);
                t.setCharacterSize(30); 
                break;
            case 2: //map creator
                t.setString("Mapped by: " + infoStrings[i]);
                t.setFillColor(sf::Color::White);
                t.setPosition(songRect.getPosition().x + 200, songRect.getPosition().y + 50);
                t.setCharacterSize(30); 
                break;
            case 3: //difficulty
                t.setString("[" + infoStrings[i] + "]");
                t.setFillColor(sf::Color::White);
                t.setPosition(songRect.getPosition().x + 300, songRect.getPosition().y + 50);
                t.setCharacterSize(30); 
                break;
            }

            window.draw(t);
        }
    }

    void drawButton(sf::RenderWindow &window)
    {
        window.draw(songRect);
        drawInfo(window);
    }

    void setPosition(sf::Vector2f pos) { songRect.setPosition(pos); }

    sf::Vector2f getPosition() const { return songRect.getPosition(); }

    void arrangeButtons(std::vector<MapSelectButton> &buttons)
    {
        for(int i = 0; i < buttons.size(); ++i)
        {
            if(i > 0)
                buttons[i].setPosition({buttons[i - 1].getPosition().x , buttons[i - 1].getPosition().y + 175});
        }
    }
};