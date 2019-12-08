#include <SFML/Graphics.hpp>

#include"playField.h"
#include"hitCircle.h"


int main()
{
	float osuPx;
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "osu!",sf::Style::Fullscreen);
	
	sf::Clock runTime;
	//Objects created=================================================================================
	PlayField playField(screenSize,osuPx);
	HitCircle circle({ 500.0f,607.0f }, 4.0f, osuPx, 1.8f);
	//================================================================================================
	
	//Other utilities=================================================================================
	sf::Clock deltaClock;
	sf::Time deltaTime;
	//================================================================================================
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//Render stuff to screen ====================================================
		window.clear();

		window.draw(playField.getPlayField());

		circle.approachTheCircle(deltaTime.asSeconds());
		circle.drawCircle(window);

		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}
	circle.clearApproachCircleFromMemory();
	return 0;
}