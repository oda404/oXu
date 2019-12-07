#include <SFML/Graphics.hpp>

#include"playField.h"
#include"createCircle.h"

int main()
{
	float osuPx;
	sf::Vector2f screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x,screenSize.y), "osu!");
	
	sf::Clock runTime;
	//Objects created=================================================================================
	PlayField playField(screenSize,osuPx);
	Circle circle({ 64,64 }, { 400.0f,400.0f }, 2.0f, { 70,70 },4.0f,osuPx);
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
		//window.draw(circle.getApproachCircle());
		window.draw(circle.getHitCircle());

		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}
	circle.clearCirclesFromMemory();
	return 0;
}