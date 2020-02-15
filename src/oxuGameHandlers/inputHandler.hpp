#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

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
 
        void handleInput(HitObjectManager &hitObj, sf::RenderWindow &window)
        {  

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            {
                for(unsigned int i = hitObj.getHitCircleIt(); i > hitObj.getHitCircleCap(); --i)
                {
                    hitObj.get(i);
                }
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {

            }
        }
    };
}