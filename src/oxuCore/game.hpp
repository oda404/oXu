#pragma once
#include<SFML/Graphics.hpp>
#include<memory>

#include"sceneManager.h"

namespace oxu
{
    class Game
    {
    private:
        sf::Vector2i screenSize = { 1920,1080 };
        sf::RenderWindow window;

    public:
        Game()
        {
            window.create(sf::VideoMode(screenSize.x, screenSize.y), "oXu");
        }

        void run()
        {
            sf::Clock deltaClock;
            sf::Time deltaTime;

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                deltaTime = deltaClock.restart();
                window.clear();

                window.display();

            }
        }

    };
}