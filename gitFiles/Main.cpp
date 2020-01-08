#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include"playField.h"
#include"hitObject.h"
#include"beatMap.h"
#include<vector>

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "osu!",sf::Style::Fullscreen);
	
	sf::Clock runTime;
	//Objects created=================================================================================
	PlayField playField(screenSize);
	BeatMap map(829296);
	HitObject circle({ 66,50 },500, 2.5f, 1.8f, playField);
	HitObject slider({ 100,180 },500, 2.5f, 1.8f, playField, 'L');
	
	//================================================================================================
	std::cout << map.getHitObjectPositions()[0].x;
	//rect.setRotation(std::atan2(265.0f - 311.0f, 328.0f - 309.0f) * 180.0f / 3.1415f);

	//Other utilities=================================================================================
	sf::Clock deltaClock;
	sf::Time deltaTime;
	//================================================================================================

	sf::Vector2f pos0 = { 66,50 };
	sf::Vector2f pos1 = { 63,330 };
	sf::Vector2f pos2 = { 171,50 };
	sf::Vector2f pos3 = { 214,351 };
	sf::Vector2f pos4 = { 300,24 };
	sf::Vector2f pos5 = { 338,354 };
	sf::Vector2f pos6 = { 438,151 };

	std::vector<sf::Vector2f> positions = {pos0, pos1,pos2,pos3,pos4,pos5,pos6};
	
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
		//slider.moveOnStraightPath((80.0f / (0.8f * 100.0f) * 300.0f)/1000.0f, deltaTime.asSeconds(), playField);
		slider.drawCircle(window);
		
		circle.approachTheCircle(deltaTime.asSeconds());
		//circle.drawBezierCurve(positions,playField,window);
		circle.moveOnBezierCurve(playField, deltaTime.asSeconds(),positions,500,window);
		circle.drawCircle(window);
		
		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}
	return 0;
}