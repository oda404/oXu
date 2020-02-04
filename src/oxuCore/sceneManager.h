#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

#include"button.h"
#include"../oxuGameHandlers/graphicsHandler.hpp"
#include"../oxuGameHandlers/soundHandler.h"

namespace oxu
{
    class SceneManager
    {
    private:
        GraphicsHandler *graphicsHandler;
        SoundHandler *soundHandler;
        std::uint8_t currentScene;

    public:
        SceneManager(GraphicsHandler *graphicsHandlerPtr, SoundHandler *soundHandlerPtr):
        graphicsHandler(graphicsHandlerPtr), soundHandler(soundHandlerPtr), currentScene(0) { }

        void handleCurrentScene(sf::RenderWindow &window, const float &dt)
        {
            graphicsHandler->handleGraphics(window, dt, currentScene);
            soundHandler->handleSound(currentScene);
        }

    };
}