#include <SFML/Graphics.hpp>

#include"playField.h"
#include"beatMapParser.h"
#include"hitObjectLoader.h"

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "osu!");
	window.setFramerateLimit(480);

	PlayField playField(screenSize);

	BeatMapParser map;

	HitObjectLoader aw;
	aw.createHitObjects(map, playField);
	
	//rect.setRotation(std::atan2(265.0f - 311.0f, 328.0f - 309.0f) * 180.0f / 3.1415f);

	

	sf::Clock deltaClock;
	sf::Time deltaTime;
	
	while (window.isOpen())
	{
		static sf::Clock mapTime;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//Render stuff to screen ====================================================
		window.clear();

		for (unsigned int i = 0; i < aw.hitCircleVector.size() - (aw.hitCircleVector.size() - 10); i++)
		{
			if (mapTime.getElapsedTime().asMilliseconds() >= aw.hitCircleVector[i].getSpawnTime() && !aw.approachCircleVector[i].getApproachState())
			{
				window.draw(aw.approachCircleVector[i].getApproachCircle());
				window.draw(aw.hitCircleVector[i].getHitCircle());
				aw.approachCircleVector[i].approachTheCircle(deltaTime.asSeconds(),aw.hitCircleVector[i].getHitCircleScale());

				if(i > 0 )
					if(aw.approachCircleVector[i - 1].getApproachState())
					{
						aw.approachCircleVector.erase(aw.approachCircleVector.begin() + 0);
						aw.hitCircleVector.erase(aw.hitCircleVector.begin() + 0);
					}
			}
		}

		for(unsigned int i = 0; i < aw.sliderVector.size(); i++)
		{
			if (mapTime.getElapsedTime().asMilliseconds() >= aw.sliderVector[i].getSpawnTime() && !aw.sliderApproachCircles[i].getApproachState())
			{
				window.draw(aw.sliderVector[i].getHitCircle());
				window.draw(aw.sliderApproachCircles[i].getApproachCircle());
				aw.sliderApproachCircles[i].approachTheCircle(deltaTime.asSeconds(), aw.sliderVector[i].getHitCircleScale());
			}
			else if(aw.sliderApproachCircles[i].getApproachState())
			{
				window.draw(aw.sliderVector[i].getHitCircle());
				aw.sliderVector[i].moveOnStraightPath(deltaTime.asSeconds(), playField,aw.sliderApproachCircles[i]);

				if(aw.sliderVector[i].getSlides() == 0)
				{
					aw.sliderVector.erase(aw.sliderVector.begin() + i);
					aw.sliderApproachCircles.erase(aw.sliderApproachCircles.begin() + i);
				}
			}
			
		}
		
		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}
	return 0;
}