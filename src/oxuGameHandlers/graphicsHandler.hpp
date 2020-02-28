// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include<functional>
#include<tuple>
#include<iostream>

#include "hitObjectManager.hpp"
#include "../oxuGameComponents/playField.hpp"
#include"../oxuGameHandlers/mapManager.hpp"
#include"soundHandler.hpp"
#include"inputHandler.hpp"


namespace oxu
{
    class GraphicsHandler
    {
    private:
        HitObjectManager *hitObjects;
        SoundHandler *mapSound; 
        PlayField *playField;
        InputHandler *inputHandler;
        MapManager *mapManager;

        std::vector<MapSelectButton> *mapSelectButtons;

        sf::Font font;
        sf::Text comboString;
        sf::Text scoreText;
        sf::RectangleShape xButton;
        sf::RectangleShape zButton;

        sf::Texture cursorTexture;
        sf::Texture cursorTrailTexture;
        std::vector<sf::Vector2f> cursorTrailVector;
        std::shared_ptr<sf::Sprite> cursorSprite;

        std::vector<sf::Texture> hitScoreTextures;

        std::vector<std::vector<std::function<void (sf::RenderWindow &window, const float &dt)>>> sceneGraphicsHandlers;

        void drawPendingObjectScoring(sf::RenderWindow &window, const float &dt);

    public:
        GraphicsHandler(InputHandler *inputHandler, HitObjectManager *hitObjPtr, SoundHandler *soundHandlerPtr, PlayField *playFieldPtr, MapManager *mapManagerPtr, std::vector<MapSelectButton> *buttonsPtr);

        void handleGraphics(sf::RenderWindow &window, const float &dt, const std::uint8_t &sceneID);

        void drawHitCircles(sf::RenderWindow &window, const float &dt);

        void drawGameOverlay(sf::RenderWindow &window, const float &dt);

        void setCursor(sf::RenderWindow *window);

    #ifdef __linux__
        void drawCursor(sf::RenderWindow *window, sf::Vector2f mousePos);
    #endif

        void drawMainMenu(sf::RenderWindow &window, const float &dt);

        void drawSongSelectMenu(sf::RenderWindow &window, const float &dt);
    };
}
