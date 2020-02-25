#include"game.hpp"

oxu::Game::Game()
{
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(screenSize.x, screenSize.y), "oXu");
    window->setFramerateLimit(120);

	playField =  std::make_shared<PlayField>(window->getSize());

    hitObjects = std::make_shared<HitObjectManager>(playField.get());

	mapManager = std::make_shared<MapManager>(&mapSelectionButtons);

    inputHandler = std::make_shared<InputHandler>(hitObjects.get(), &soundHandler, mapManager.get(), &mapSelectionButtons);

    graphicsHandler = std::make_shared<GraphicsHandler>(inputHandler.get(), hitObjects.get(), &soundHandler, playField.get(), mapManager.get(), &mapSelectionButtons);
    graphicsHandler->setCursor(window.get());

}

void oxu::Game::run()
{
	std::vector<std::future<void>> futures;

    while (window->isOpen())
	{
		deltaTime = deltaClock.restart();

		sf::Event event;
		while (window->pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				soundHandler.setVolumeToDefault();
				soundHandler.freeAudio();
				window->close();
				break;

			case sf::Event::MouseWheelScrolled:
				if(currentScene == 1)
					mapSelectionButtons[0].scrollButtons(mapSelectionButtons, event.mouseWheelScroll.delta);
				else if(currentScene == 2)
					futures.push_back(std::async(std::launch::async, soundHandler.scrollVolume, event.mouseWheelScroll.delta));
				break;
			
			case sf::Event::KeyPressed:
				inputHandler->handleInput(*window, currentScene);
				break;
				
			default:
				break;
			}
		}

		if(currentScene == 2)
			window->clear();
		else
			window->clear(sf::Color(100,100,100,255));

		//================  Actual scene handling  ==================
		graphicsHandler->handleGraphics(*window.get(), deltaTime.asSeconds(), currentScene);

		inputHandler->handleInput(*window.get(), currentScene);
		//===========================================================
	#ifdef __linux__
		graphicsHandler->drawCursor(window.get(), static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)));
	#endif
		window->display();
	}
}