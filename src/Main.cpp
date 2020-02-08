#include <SFML/Graphics.hpp>

#include"oxuGameComponents/playField.h"
#include"oxuCore/sceneManager.h"

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "oXu");
	window.setFramerateLimit(120);

	oxu::PlayField playField(screenSize);

	//rect.setRotation(std::atan2(265.0f - 311.0f, 328.0f - 309.0f) * 180.0f / 3.1415f);

	sf::Clock deltaClock;
	sf::Time deltaTime;

	oxu::SceneManager sc(&playField);

	while (window.isOpen())
	{
		deltaTime = deltaClock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color(100,100,100,255));

		sc.handleCurrentScene(window, deltaTime.asSeconds());

		window.display();
	}

	return 0;
}