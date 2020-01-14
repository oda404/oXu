#include <SFML/Graphics.hpp>

#include"playField.h"
#include"beatMap.h"
#include"hitObjectLoader.h"

#include<vector>
#include<iostream>

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "osu!");
	window.setFramerateLimit(480);

	PlayField playField(screenSize);

	BeatMap map;

	HitObjectLoader aw;
	aw.createHitObjects(map, playField);
	
	//rect.setRotation(std::atan2(265.0f - 311.0f, 328.0f - 309.0f) * 180.0f / 3.1415f);

	sf::Clock deltaClock;
	sf::Time deltaTime;
	int deletedObj = 0;
	
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

		for (unsigned int i = 0; i < aw.hitCircleVector.size() - (aw.hitCircleVector.size() - 20); i++)
		{
			if ((mapTime.getElapsedTime().asMilliseconds() >= aw.hitCircleVector[i].getSpawnTime() && !aw.approachCircleVector[i].getApproachState()) || !aw.hitCircleVector[i].isDoneSliding())
			{
				if(map.getHitObjectCurveType()[i] == 'N')
				{
					window.draw(aw.approachCircleVector[i].getApproachCircle());
					window.draw(aw.hitCircleVector[i].getHitCircle());
					aw.approachCircleVector[i].approachTheCircle(deltaTime.asSeconds(),aw.hitCircleVector[i].getHitCircleScale());
				}
				else if(map.getHitObjectCurveType()[i] == 'B')
				{
					window.draw(aw.hitCircleVector[i].getHitCircle());
					if(!aw.approachCircleVector[i].getApproachState())
					{
						aw.approachCircleVector[i].approachTheCircle(deltaTime.asSeconds(),aw.hitCircleVector[i].getHitCircleScale());
						window.draw(aw.approachCircleVector[i].getApproachCircle());
					}
					else 
					{
						aw.hitCircleVector[i].moveOnBezierCurve(playField,deltaTime.asSeconds(),aw.approachCircleVector[i]);
					}
				}
				
				if(i > 0)
					if(aw.approachCircleVector[i - 1].getApproachState() && aw.hitCircleVector[i - 1].isDoneSliding()) 
					{
						aw.approachCircleVector.erase(aw.approachCircleVector.begin() + 0);
						aw.hitCircleVector.erase(aw.hitCircleVector.begin() + 0);
						map.eraseFirstCurveTypeFromVector();

					}
			}
		}
		
		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}
	return 0;
}