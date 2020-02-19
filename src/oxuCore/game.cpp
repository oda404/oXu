#include"game.hpp"

oxu::Game::Game()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(screenSize.x, screenSize.y), "oXu");
    window->setFramerateLimit(120);

	playField =  std::make_shared<PlayField>(window->getSize());

    hitObjects = std::make_shared<HitObjectManager>(playField.get());

    inputHandler = std::make_shared<InputHandler>(hitObjects.get(), &soundHandler);

    graphicsHandler = std::make_shared<GraphicsHandler>(inputHandler.get(), hitObjects.get(), &soundHandler, playField.get());
    graphicsHandler->setCursor(window.get());
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

		if(currentScene == 1)
			window->clear();
		else
			window->clear(sf::Color(100,100,100,255));
				
	#ifdef __linux__
		graphicsHandler->drawCursor(*window.get());
	#endif
		
		//================  Actual scene handling  ==================
		soundHandler.handleSound(currentScene);

		graphicsHandler->handleGraphics(*window.get(), deltaTime.asSeconds(), currentScene);

		inputHandler->handleInput(*window.get(), currentScene);
		//===========================================================

		window->display();
	}
}