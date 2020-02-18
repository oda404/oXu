#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<functional>

#include"hitObjectManager.h"

namespace oxu
{
    class InputHandler
    {
    private:
        sf::Keyboard kb;
        sf::Vector2i mousePos;

        HitObjectManager *hitObjManager;
        SoundHandler *soundHandler;

        bool xState = false, zState = false;
        int combo = 0, pendingObj = 0;

        std::vector<std::function<void(sf::RenderWindow &window)>> sceneInputHandlers;

        float getApproachCirclePercentage(const float &spawnTime, const float &approachSpeed, const float &playingOffset) const
        {
            return 100 - (spawnTime - playingOffset) * 100 / approachSpeed;
        }
        
    public:
        InputHandler(HitObjectManager *hitObjManagerPtr, SoundHandler *soundHandlerPtr):
        hitObjManager(hitObjManagerPtr), soundHandler(soundHandlerPtr)
        {
            //==========  main menu input handlers ====================
            sceneInputHandlers.push_back([this](sf::RenderWindow &window) -> void { return this->handleButtons(window); });

            //========== game input handler ==========================
            sceneInputHandlers.push_back([this](sf::RenderWindow &window) -> void { return this->handleHitObjects(window); });
        }

        bool getXKeyState() const { return xState; }

        bool getZKeyState() const { return zState; }

        int getCombo() const { return combo; }

        void handleInput(sf::RenderWindow &window, std::uint8_t &sceneID)
        {   
            sceneInputHandlers[sceneID](window);
        }

        void handleButtons(sf::RenderWindow &window)
        {

        }

        void handleHitObjects(sf::RenderWindow &window)
        {
            if(kb.isKeyPressed(sf::Keyboard::X))
            {
                xState = true;

                int ACPerc = getApproachCirclePercentage(hitObjManager->getHitCircleByIndex(pendingObj)->getSpawnTime(), 450, soundHandler->getAudioPlayingOffset());

                if(ACPerc > 90 && ACPerc <= 100 )
                {
                    ++combo;
                    ++pendingObj;
                }          
            }
            else
                xState = false;

            /*if(kb.isKeyPressed(sf::Keyboard::Z))
            {
                zState = true;
                mousePos = sf::Mouse::getPosition(window);

                int ACPerc = getApproachCirclePercentage(hitObjManager->getHitCircleByIndex(pendingObj)->getSpawnTime(), 450, soundHandler->getAudioPlayingOffset());

                if(ACPerc > 90 && ACPerc <= 100 )
                {
                    ++combo;
                    ++pendingObj;
                }
            }
            else
                zState = false;*/

            if(getApproachCirclePercentage(hitObjManager->getHitCircleByIndex(pendingObj)->getSpawnTime(), 450, soundHandler->getAudioPlayingOffset()) > 100)
            {
                combo = 0;
                ++pendingObj;
            }
        } 
    };
}