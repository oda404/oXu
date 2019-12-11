#include <SFML/Graphics.hpp>

#include"playField.h"
#include"hitCircle.h"
//#include"beatMap.h"
#include"slider.h"

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "osu!",sf::Style::Fullscreen);
	
	sf::Clock runTime;
	//Objects created=================================================================================
	PlayField playField(screenSize);
	HitCircle circle({ 65.0f,21.0f }, 4.2f, 1.8f, playField);
	Slider slider({ 309.0f,311.0f }, 5.2f, 1.0f, playField, 'L', { 328.0f, 265.0f });
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
		
		slider.getSliderStartPos().approachTheCircle(deltaTime.asSeconds());
		slider.getSliderStartPos().drawCircle(window);
		
		circle.approachTheCircle(deltaTime.asSeconds());
		circle.drawCircle(window);

		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}
	slider.deleteSliderStartPoint();
	circle.clearApproachCircleFromMemory();
	return 0;
}