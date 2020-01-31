#pragma once
#include<SFML/Graphics.hpp>

class Button
{
private:
    sf::Vector2f buttonPos;
public:
    Button(const sf::Vector2f &pos):
    buttonPos(pos)
    {
        
    }
};