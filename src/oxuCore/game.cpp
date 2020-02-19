#include"game.hpp"

oxu::Game::Game()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(screenSize.x, screenSize.y), "oXu");
    window->setFramerateLimit(120);

    sceneManager = std::make_shared<SceneManager>(window.get());
}

void oxu::Game::run()
{

    while (window->isOpen())
	{
		deltaTime = deltaClock.restart();

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		sceneManager->handleCurrentScene(*window, deltaTime.asSeconds());
	}
}