#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include"playField.h"
#include"beatMapParser.h"
#include"hitObjectLoader.h"
#include"StandardCursor.hpp"
#include"graphicsHandler.hpp"

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "oXu");
	window.setFramerateLimit(120);

	oxu::PlayField playField(screenSize);

	oxu::GraphicsHandler graph;
	graph.setCursor(window);

	oxu::BeatMapParser map;

	oxu::HitObjectLoader aw;
	aw.createHitObjects(map, playField);
	
	
	sf::Music m;
	m.openFromFile("yomi.ogg");
	m.setVolume(2);

	//rect.setRotation(std::atan2(265.0f - 311.0f, 328.0f - 309.0f) * 180.0f / 3.1415f);

	sf::Clock deltaClock;
	sf::Time deltaTime;

	while (window.isOpen())
	{
		deltaTime = deltaClock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (m.getStatus() == sf::Sound::SoundSource::Stopped)
			m.play();
		
		window.clear();

		graph.drawCursor(window);
		graph.drawHitCircles(aw, m.getPlayingOffset().asMilliseconds(), deltaTime.asSeconds(), window);
		graph.drawSliders(aw, m.getPlayingOffset().asMilliseconds(), deltaTime.asSeconds(), playField, window);

		window.display();

	}

	return 0;
}