#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

#include"hitObjectManager.h"

namespace oxu
{
    class InputHandler
    {
    private:
        sf::SoundBuffer buffer;
        sf::Sound sound;
    public:

        InputHandler()
        {
            buffer.loadFromFile("/root/Documents/osuBootleg/src/soft-hitnormal.wav");
            sound.setBuffer(buffer);
            sound.setVolume(20);
        }
 
        void handleInput(HitObjectManager &hitObj)
        {  

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            {
                
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {

            }
        }
    };
}