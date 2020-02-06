#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

#include"../oxuGameHandlers/graphicsHandler.hpp"
#include"../oxuGameHandlers/soundHandler.h"
#include"../oxuGameHandlers/beatMapParser.h"
#include"../oxuGameHandlers/hitObjectLoader.h"
#include"../oxuGameComponents/playField.h"
#include"button.h"

namespace oxu
{
    class SceneManager
    {
    private:
        GraphicsHandler *graphicsHandler;
        SoundHandler *soundHandler;
        PlayField *playField;
        std::uint8_t currentScene;
        std::vector<std::vector<Button>> buttons;

    public:
        SceneManager(GraphicsHandler *graphicsHandlerPtr, SoundHandler *soundHandlerPtr, PlayField *playFieldPtr):
        graphicsHandler(graphicsHandlerPtr), soundHandler(soundHandlerPtr), playField(playFieldPtr) , currentScene(0)
        {
            std::vector<Button> aux;
            aux.emplace_back(sf::Vector2f({0,0}),sf::Vector2f({1920,1080}), 1);

            buttons.push_back(aux);
            aux.clear();
        }

        void handleCurrentScene(sf::RenderWindow &window, const float &dt)
        {
            soundHandler->handleSound(currentScene);
            graphicsHandler->handleGraphics(window, dt, currentScene);

            for(auto button: buttons[0])
            {
                button.handleButton(currentScene);
            }
        }

        void loadBeatMap()
        {
            BeatMapParser parser;
            HitObjectLoader loader;
            loader.createHitObjects(parser, *playField);
        }

    };
}