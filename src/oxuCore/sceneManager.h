#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

#include"button.h"
#include"../oxuGameHandlers/graphicsHandler.hpp"

namespace oxu
{
    class SceneManager
    {
    private:
        GraphicsHandler *graphicsHandler;
        std::uint8_t currentScene;

    public:
        SceneManager(GraphicsHandler *graphicsHandlerPtr):
        graphicsHandler(graphicsHandlerPtr), currentScene(0) { }

        void handleCurrentScene(sf::RenderWindow &window, const float &dt)
        {
            graphicsHandler->handleGraphics(window, dt, currentScene);
        }

    };
}