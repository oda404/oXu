#include <SFML/Graphics.hpp>

#include<iostream>
#include<cmath>
#include"playField.h"
#include"hitObject.h"

float getPt(float n1, float n2, float perc)
{
	float diff = n2 - n1;

	return n1 + (diff * perc);
}

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "osu!",sf::Style::Fullscreen);
	
	sf::Clock runTime;
	//Objects created=================================================================================
	PlayField playField(screenSize);
	HitObject circle({ 65.0f,21.0f }, 4.2f, 1.8f, playField);
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
		slider.slideTheSlider(1.0f, deltaTime.asSeconds(), playField);
		slider.drawCircle(window);

		circle.approachTheCircle(deltaTime.asSeconds());
		circle.drawCircle(window);

		for( float i = 0 ; i < 1 ; i += 0.001 )
		{
			float xa = getPt( 98 , 285, i );
			float ya = getPt(75, 67, i );
			float xb = getPt(285, 370, i );
			float yb = getPt(67, 192, i );

			float x = getPt( xa , xb , i );
			float y = getPt( ya , yb , i );

			rect1.setPosition(x, y);
			window.draw(rect1);
		}

		window.draw(rect);
		
		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}
	return 0;
}