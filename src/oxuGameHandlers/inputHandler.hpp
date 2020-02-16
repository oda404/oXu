#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

#include"hitObjectManager.h"

namespace oxu
{
    class InputHandler
    {
    private:
        sf::Keyboard kb;
        
    public:

        InputHandler()
        {

        }
 
        void handleInput(HitObjectManager &hitObj, sf::RenderWindow &window, SoundHandler &soundH)
        {  
            if(kb.isKeyPressed(sf::Keyboard::X))
            {
                for(unsigned int i = hitObj.getHitCircleIt(); i > hitObj.getHitCircleCap(); --i)
                {
                    if( sf::Mouse::getPosition().x >= hitObj.getHitCircleByIndex(i)->getPos().x - hitObj.getHitCircleSize() / 2 &&
                        sf::Mouse::getPosition().x <= hitObj.getHitCircleByIndex(i)->getPos().x + hitObj.getHitCircleSize() / 2 &&
                        sf::Mouse::getPosition().y >= hitObj.getHitCircleByIndex(i)->getPos().y - hitObj.getHitCircleSize() / 2 &&
                        sf::Mouse::getPosition().y <= hitObj.getHitCircleByIndex(i)->getPos().y + hitObj.getHitCircleSize() / 2 )
                    {
                       
                    }
                }
            }
            else if(kb.isKeyPressed(sf::Keyboard::Z))
            {
                for(unsigned int i = hitObj.getHitCircleIt(); i > hitObj.getHitCircleCap(); --i)
                {
                    if( sf::Mouse::getPosition().x >= hitObj.getHitCircleByIndex(i)->getPos().x - hitObj.getHitCircleSize() / 2 &&
                        sf::Mouse::getPosition().x <= hitObj.getHitCircleByIndex(i)->getPos().x + hitObj.getHitCircleSize() / 2 &&
                        sf::Mouse::getPosition().y >= hitObj.getHitCircleByIndex(i)->getPos().y - hitObj.getHitCircleSize() / 2 &&
                        sf::Mouse::getPosition().y <= hitObj.getHitCircleByIndex(i)->getPos().y + hitObj.getHitCircleSize() / 2 )
                    {
                        
                    }
                }
            }
        }
    };
}