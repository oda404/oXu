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
        MapManager *mapManager;

        std::vector<MapSelectButton> *mapSelectButtons;

        bool xState = false, zState = false, mousePressed = false;
        int combo = 0, pendingObj = 0;

        std::vector<std::function<void(sf::RenderWindow &window, std::uint8_t &currentScene)>> sceneInputHandlers;

        float getApproachCirclePercentage(const float &spawnTime, const float &approachSpeed, const float &playingOffset) const
        {
            return 100 - (spawnTime - playingOffset) * 100 / approachSpeed;
        }
        
    public:
        InputHandler(HitObjectManager *hitObjManagerPtr, SoundHandler *soundHandlerPtr, MapManager *mapManagerPtr, std::vector<MapSelectButton> *mapSelectButtons):
        hitObjManager(hitObjManagerPtr), soundHandler(soundHandlerPtr), mapManager(mapManagerPtr), mapSelectButtons(mapSelectButtons)
        {
            //==========  main menu input handlers ====================
            sceneInputHandlers.push_back([this](sf::RenderWindow &window, std::uint8_t &currentScene) -> void { return this->handleMainMenuInput(window, currentScene); });

            //========== song select input handler ====================
            sceneInputHandlers.push_back([this](sf::RenderWindow &window, std::uint8_t &currentScene) -> void { return this->handleSongSelectInput(window, currentScene); });

            //========== game input handler ==========================
            sceneInputHandlers.push_back([this](sf::RenderWindow &window, std::uint8_t &currentScene) -> void { return this->handleHitObjectsInput(window, currentScene); });
        }

        bool getXKeyState() const { return xState; }

        bool getZKeyState() const { return zState; }

        int getCombo() const { return combo; }

        void handleInput(sf::RenderWindow &window, std::uint8_t &sceneID)
        {   
            sceneInputHandlers[sceneID](window, sceneID);
        }

        void handleMainMenuInput(sf::RenderWindow &window, std::uint8_t &currentScene)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mousePressed)
            {
                mousePressed = true;
                ++currentScene;
            }
            else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                mousePressed = false;
        }

        void handleSongSelectInput(sf::RenderWindow &window, std::uint8_t &currentScene)
        {
            for(auto &button: *mapSelectButtons)
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && button.checkClick(sf::Mouse::getPosition(window)) && !mousePressed)
                {
                    mapManager->loadHitObjects(button.getMapPath());
                    hitObjManager->createHitObjects(*mapManager);

                    mousePressed = true;
                    ++currentScene;
                }
                else
                    mousePressed = false;
            }
        }

        void handleHitObjectsInput(sf::RenderWindow &window, std::uint8_t &currentScene)
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

            if(getApproachCirclePercentage(hitObjManager->getHitCircleByIndex(pendingObj)->getSpawnTime(), 450, soundHandler->getAudioPlayingOffset()) > 100)
            {
                combo = 0;
                ++pendingObj;
            }
        } 
    };
}