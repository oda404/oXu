#include <SFML/Graphics.hpp>
#include<iostream>

#include"approachCircle.h"
#include"hitCircle.h"

sf::Clock runTime;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "osu!", sf::Style::Fullscreen);
	
	//Sprites used====================================================================================
	ApproachCirclesSprites approachCircle(0.450f, { 70,70 },{400.0f,400.0f},{2.0f,2.0f});
	HitCircleSprites hitCircle({64,64},{400.0f,400.0f});
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
		
		if (approachCircle.getApproachCircle().getScale().x > 1.0f)
			approachCircle.approachTheCircle(deltaTime.asSeconds());
		
		window.draw(approachCircle.getApproachCircle());
		window.draw(hitCircle.getHitCircle());

		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}

	return 0;
}