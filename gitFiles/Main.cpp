#include <SFML/Graphics.hpp>

#include"approachCircle.h"
#include"hitCircle.h"
#include"playField.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920,1080), "osu!",sf::Style::Fullscreen);
	
	sf::Clock runTime;

	//Objects created=================================================================================
	ApproachCirclesSprites approachCircle(0.800f, { 70,70 },{400.0f,400.0f},{2.0f,2.0f});
	HitCircleSprites hitCircle({64,64},{400.0f,400.0f});
	PlayField playField({ 1344.0f,1008.0f },1920,1080);
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
		
		window.draw(playField.getPlayField());
		window.draw(approachCircle.getApproachCircle());
		window.draw(hitCircle.getHitCircle());

		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}

	return 0;
}