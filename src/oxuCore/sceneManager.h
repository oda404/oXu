#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

#include"../oxuGameHandlers/graphicsHandler.hpp"
#include"../oxuGameHandlers/soundHandler.h"
#include"button.h"

namespace oxu
{
    class SceneManager
    {
    private:
        GraphicsHandler *graphicsHandler;
        SoundHandler *soundHandler;
        std::uint8_t currentScene;
        std::vector<std::vector<Button>> buttons;

    public:
        SceneManager(GraphicsHandler *graphicsHandlerPtr, SoundHandler *soundHandlerPtr):
        graphicsHandler(graphicsHandlerPtr), soundHandler(soundHandlerPtr), currentScene(0)
        {
            std::vector<Button> aux;
            aux.emplace_back(sf::Vector2f({0,0}),sf::Vector2f({1920,1080}),Action::ChangeScene);

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

    };
}