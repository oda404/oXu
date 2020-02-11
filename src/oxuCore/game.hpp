#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<memory>

#include"../oxuGameComponents/playField.h"
#include"sceneManager.h"

namespace oxu
{
    class Game
    {
    private:

        sf::Vector2i screenSize = { 1920,1080 };
        std::shared_ptr<sf::RenderWindow> window;
        std::shared_ptr<PlayField> playField;
        std::shared_ptr<SceneManager> sceneManager;

        sf::Clock deltaClock;
	    sf::Time deltaTime;

    public:
        Game();

        void run();

    };
}