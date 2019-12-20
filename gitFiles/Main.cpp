#include <SFML/Graphics.hpp>

#include<iostream>
#include<cmath>
#include"playField.h"
#include"hitObject.h"

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "osu!",sf::Style::Fullscreen);
	
	sf::Clock runTime;
	//Objects created=================================================================================
	PlayField playField(screenSize);
	HitObject circle({ 70.0f,26.0f }, 4.0f, 1.8f, playField);
	HitObject slider({ 309.0f,311.0f }, 5.2f, 1.8f, playField, 'L', { 328.0f, 265.0f });
	
	//================================================================================================
	
	sf::RectangleShape rect;
	rect.setPosition(slider.getPos());
	rect.setSize({ 50 * 2.25,5 });
	rect.setRotation(std::atan2(265.0f - 311.0f, 328.0f - 309.0f) * 180.0f / 3.1415f);

	sf::RectangleShape rect1;
	rect1.setSize({ 2,2 });

	//Other utilities=================================================================================
	sf::Clock deltaClock;
	sf::Time deltaTime;
	//================================================================================================

	sf::Vector2f gizm;

	sf::Vector2f pos0 = { 70,26 };
	sf::Vector2f pos1 = { 461,37 };
	sf::Vector2f pos2 = { 137,165 };
	sf::Vector2f pos3 = { 429,147 };

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

		for (float t = 0; t < 1; t += 0.001f)
		{
			gizm = (std::pow(1 - t, 3) * pos0 + 3* std::pow(1-t,2) * t * pos1 + 3 * (1 - t) * std::pow(t,2) * pos2 + std::pow(t,3) * pos3)*playField.getOsuPx() ;
			rect1.setPosition(playField.getPlayFieldStartPoint()+gizm);
			window.draw(rect1);
		}

		circle.approachTheCircle(deltaTime.asSeconds());
		circle.moveOnBezierCurve(playField, deltaTime.asSeconds());
		circle.drawCircle(window);
		
		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}
	return 0;
}