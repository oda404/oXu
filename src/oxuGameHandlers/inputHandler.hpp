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
        sf::Vector2i mousePos;
        bool f = true;

        float getApproachCirclePercentage(const float &spawnTime, const float &approachSpeed, const float &playingOffset) const
        {
            return 100 - (spawnTime - playingOffset) * 100 / approachSpeed;
        }
        
    public:
        InputHandler() { }
 
        void handleInput(HitObjectManager &hitObj, sf::RenderWindow &window, SoundHandler &soundH)
        {   
            if(kb.isKeyPressed(sf::Keyboard::X))
            {
                mousePos = sf::Mouse::getPosition(window);
                for(unsigned int i = hitObj.getHitCircleIt(); i > hitObj.getHitCircleCap(); --i)
                {
                    if(hitObj.getHitCircleByIndex(i)->canBeClicked())
                    {
                        if( mousePos.x >= hitObj.getHitCircleByIndex(i)->getPos().x - hitObj.getHitCircleSize() / 2 &&
                            mousePos.x <= hitObj.getHitCircleByIndex(i)->getPos().x + hitObj.getHitCircleSize() / 2 &&
                            mousePos.y >= hitObj.getHitCircleByIndex(i)->getPos().y - hitObj.getHitCircleSize() / 2 &&
                            mousePos.y <= hitObj.getHitCircleByIndex(i)->getPos().y + hitObj.getHitCircleSize() / 2 )
                        {
                            if(getApproachCirclePercentage(hitObj.getHitCircleByIndex(i)->getSpawnTime(), hitObj.getApproachCircleByIndex(i)->getApproachSpeedAsMs(), soundH.getAudioPlayingOffset()) > 90)
                            {
                                //90 is a percentage
                                hitObj.getHitCircleByIndex(i)->click();
                            }
                        }
                    }
                }
            }
            if(kb.isKeyPressed(sf::Keyboard::Z))
            {
                mousePos = sf::Mouse::getPosition(window);
                for(unsigned int i = hitObj.getHitCircleIt(); i > hitObj.getHitCircleCap(); --i)
                {
                    if(hitObj.getHitCircleByIndex(i)->canBeClicked())
                    {
                        if( mousePos.x >= hitObj.getHitCircleByIndex(i)->getPos().x - hitObj.getHitCircleSize() / 2 &&
                            mousePos.x <= hitObj.getHitCircleByIndex(i)->getPos().x + hitObj.getHitCircleSize() / 2 &&
                            mousePos.y >= hitObj.getHitCircleByIndex(i)->getPos().y - hitObj.getHitCircleSize() / 2 &&
                            mousePos.y <= hitObj.getHitCircleByIndex(i)->getPos().y + hitObj.getHitCircleSize() / 2 )
                        {
                            if(getApproachCirclePercentage(hitObj.getHitCircleByIndex(i)->getSpawnTime(), hitObj.getApproachCircleByIndex(i)->getApproachSpeedAsMs(), soundH.getAudioPlayingOffset()) > 90)
                            {
                                //90 is a percentage
                                hitObj.getHitCircleByIndex(i)->click();
                            }
                        }
                    }
                }
            }
        }
    };
}