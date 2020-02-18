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
        bool xState = false, zState = false;
        int combo = 0;

        float getApproachCirclePercentage(const float &spawnTime, const float &approachSpeed, const float &playingOffset) const
        {
            return 100 - (spawnTime - playingOffset) * 100 / approachSpeed;
        }
        
    public:
        InputHandler() { }

        bool getXKeyState() const { return xState; }

        bool getZKeyState() const { return zState; }

        int getCombo() const { return combo; }

        void handleInput(HitObjectManager &hitObj, sf::RenderWindow &window, SoundHandler &soundH)
        {   
            if(kb.isKeyPressed(sf::Keyboard::X))
            {
                std::cout<<soundH.getAudioPlayingOffset()<<std::endl;
                xState = true;
                mousePos = sf::Mouse::getPosition(window);
                for(unsigned int i = hitObj.getHitCircleCap(); i <= hitObj.getHitCircleIt(); ++i)
                {
                    if(hitObj.getHitCircleByIndex(i)->canBeClicked())
                    {
                        if( mousePos.x >= hitObj.getHitCircleByIndex(i)->getPos().x - hitObj.getHitCircleSize() / 2 &&
                            mousePos.x <= hitObj.getHitCircleByIndex(i)->getPos().x + hitObj.getHitCircleSize() / 2 &&
                            mousePos.y >= hitObj.getHitCircleByIndex(i)->getPos().y - hitObj.getHitCircleSize() / 2 &&
                            mousePos.y <= hitObj.getHitCircleByIndex(i)->getPos().y + hitObj.getHitCircleSize() / 2 )
                        {
                             if(getApproachCirclePercentage(hitObj.getHitCircleByIndex(i)->getSpawnTime(), 450, soundH.getAudioPlayingOffset()) > 90 &&
                            getApproachCirclePercentage(hitObj.getHitCircleByIndex(i)->getSpawnTime(), 450, soundH.getAudioPlayingOffset()) <= 100 )
                            {
                                ++combo;
                                hitObj.getHitCircleByIndex(i)->click();
                            }
                        }
                    }
                }
            }
            else
                xState = false;

            if(kb.isKeyPressed(sf::Keyboard::Z))
            {
                zState = true;
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
                            if(getApproachCirclePercentage(hitObj.getHitCircleByIndex(i)->getSpawnTime(), 450, soundH.getAudioPlayingOffset()) > 90 &&
                            getApproachCirclePercentage(hitObj.getHitCircleByIndex(i)->getSpawnTime(), 450, soundH.getAudioPlayingOffset()) <= 100 )
                            {
                                ++combo;
                                hitObj.getHitCircleByIndex(i)->click();
                            }
                        }
                    }
                }
            }
            else
                zState = false;
            
        }
    };
}