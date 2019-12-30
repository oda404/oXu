#include <SFML/Graphics.hpp>

#include<iostream>
#include<cmath>
#include"playField.h"
#include"hitObject.h"
#include<array>
#include<vector>

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "osu!",sf::Style::Fullscreen);
	
	sf::Clock runTime;
	//Objects created=================================================================================
	PlayField playField(screenSize);
	HitObject circle({ 100,68 }, 2.5f, 1.8f, playField);
	HitObject slider({ 300,300 }, 2.5f, 1.8f, playField, 'L');
	
	//================================================================================================
	
	//rect.setRotation(std::atan2(265.0f - 311.0f, 328.0f - 309.0f) * 180.0f / 3.1415f);

	//Other utilities=================================================================================
	sf::Clock deltaClock;
	sf::Time deltaTime;
	//================================================================================================

	sf::Vector2f pos0 = { 67,76 };
	sf::Vector2f pos1 = { 62,244 };
	sf::Vector2f pos2 = { 176,112 };
	sf::Vector2f pos3 = { 180,324 };
	sf::Vector2f pos4 = { 426,39 };

	std::vector<sf::Vector2f> positions = {pos0, pos1,pos2,pos3,pos4};

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
		slider.moveOnStraightPath(1.0f, deltaTime.asSeconds(), playField);
		slider.drawCircle(window);


		circle.approachTheCircle(deltaTime.asSeconds());
		circle.drawBezierCurve(positions,playField,window);
		circle.moveOnBezierCurve(playField, deltaTime.asSeconds(),positions,480);
		circle.drawCircle(window);
		
		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}
	return 0;
}