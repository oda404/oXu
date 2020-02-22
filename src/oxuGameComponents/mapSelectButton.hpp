#pragma once
#include"../oxuGameHandlers/mapManager.hpp"

class MapSelectButton
{
private:
    sf::RectangleShape songRect;
    sf::Text info;
    std::string mapPath;
    sf::Font *font;

public:
    MapSelectButton(const std::string mapPath):
    mapPath(mapPath)
    {
        songRect.setSize({700,150});
        songRect.setOutlineColor(sf::Color(0,0,0,170));
        songRect.setOutlineThickness(5);
        songRect.setFillColor(sf::Color(0,0,0, 125));
        songRect.setPosition({1920 - 700, 400});

        info.setFont(*font);
        info.setCharacterSize(45);
        info.setPosition(songRect.getPosition().x + 20, songRect.getPosition().y + 10);
        info.setFillColor(sf::Color::Black);
    }

    sf::RectangleShape getRectangle() const { return songRect; }

    void loadMapInfoText(sf::Font *ptr)
    {
        if(font == nullptr)
        {
            font = ptr;
        }

        
    }

    void drawButton(sf::RenderWindow &window, sf::Font *fontPtr)
    {
        loadMapInfoText(fontPtr);
        //?? better way of loading font and info ??

        window.draw(songRect);
        window.draw(info);
    }

    std::vector<std::string> getMapMetaData(std::string &path) const
    {
        std::ifstream map(boost::filesystem::canonical(path).string());
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
                
            }
        }
        
        return metaData;
    }
};