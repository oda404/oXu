#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include"playField.h"
#include"beatMap.h"
#include"hitObjectLoader.h"

#include<vector>

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "osu!");
	
	sf::Clock runTime;
	//Objects created=================================================================================
	PlayField playField(screenSize);

	HitObjectLoader aw;

	BeatMap map(829296);
	aw.createHitObjects(map, playField);
	//================================================================================================
	
	//rect.setRotation(std::atan2(265.0f - 311.0f, 328.0f - 309.0f) * 180.0f / 3.1415f);

	//Other utilities=================================================================================
	sf::Clock deltaClock;
	sf::Time deltaTime;
	//================================================================================================
	
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

		window.draw(playField.getPlayField());

		for (unsigned int i = 0; i < aw.hitCircleVector.size(); i++)
		{
			if (mapTime.getElapsedTime().asMilliseconds() >= aw.hitCircleVector[i]->getSpawnTime() && !aw.approachCircleVector[i]->getApproachState())
			{
				window.draw(aw.approachCircleVector[i]->getApproachCircle());
				window.draw(aw.hitCircleVector[i]->getHitCircle());
				aw.approachCircleVector[i]->approachTheCircle(deltaTime.asSeconds(),aw.hitCircleVector[i]->getHitCircleScale());
			}
		}
		
		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}
	return 0;
}