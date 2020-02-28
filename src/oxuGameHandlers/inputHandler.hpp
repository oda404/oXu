#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<functional>
#include<tuple>

#include"hitObjectManager.hpp"
#include"soundHandler.hpp"

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

        uint32_t score = 0; //score consists of the scoring of every hit circle added together for now

        std::vector<std::function<void(sf::RenderWindow &window, std::uint8_t &currentScene)>> sceneInputHandlers;

        std::vector<std::tuple<sf::Vector2f, uint8_t, uint8_t>> pendingObjScoring;

        float getApproachCirclePercentage(const float &spawnTime, const float &approachSpeed, const float &playingOffset) const;

        void hitObjectScoring(const int /* switch to float */ &ACPerc, const sf::Vector2f &objPos);

        void handleMainMenuInput(sf::RenderWindow &window, std::uint8_t &currentScene);

        void handleSongSelectInput(sf::RenderWindow &window, std::uint8_t &currentScene);

        void handleHitObjectsInput(sf::RenderWindow &window, std::uint8_t &currentScene);
        
    public:
        InputHandler(HitObjectManager *hitObjManagerPtr, SoundHandler *soundHandlerPtr, MapManager *mapManagerPtr, std::vector<MapSelectButton> *mapSelectButtons);

        bool getXKeyState() const;

        bool getZKeyState() const;

        int getCombo() const;

        uint32_t *getScore();

        std::vector<std::tuple<sf::Vector2f, uint8_t, uint8_t>> *getPendingObjScoring();

        void handleInput(sf::RenderWindow &window, std::uint8_t &sceneID);
    };
}