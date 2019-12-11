#include <SFML/Graphics.hpp>

#include"playField.h"
#include"hitCircle.h"
//#include"beatMap.h"

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "osu!",sf::Style::Fullscreen);
	
	sf::Clock runTime;
	//Objects created=================================================================================
	PlayField playField(screenSize);
	HitObject circle({ 65.0f,21.0f }, 4.2f, 1.8f, playField);
	HitObject slider({ 0.0f,0.0f }, 4.2f, 1.8f, playField, 'L', { 328.0f, 265.0f });
	//================================================================================================
	
	sf::RectangleShape rect;
	rect.setPosition(slider.getPos());
	rect.setSize({ 315 * 2.25,5 });

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
		
		slider.approachTheCircle(deltaTime.asSeconds());
		slider.drawCircle(window);
		
		circle.approachTheCircle(deltaTime.asSeconds());
		circle.drawCircle(window);

		window.draw(rect);

		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}
	slider.clearApproachCircleFromMemory();
	circle.clearApproachCircleFromMemory();
	return 0;
}