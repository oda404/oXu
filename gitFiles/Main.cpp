#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include"playField.h"
#include"hitObject.h"
#include"beatMap.h"
#include<vector>
#include<iostream>

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "osu!",sf::Style::Fullscreen);
	
	sf::Clock runTime;
	//Objects created=================================================================================
	PlayField playField(screenSize);

	sf::Texture t;
	t.setSmooth(true);
	t.loadFromFile("/root/Documents/osuBootleg/skins/hitcircle.png");

	sf::Sprite h;
	h.setTexture(t);
	h.setOrigin((sf::Vector2f)t.getSize() / 2.0f);
	h.move((sf::Vector2f)t.getSize() / 2.0f - h.getOrigin());
	h.setScale(((23.05f - (4.2f - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / t.getSize().x, ((23.05f - (4.2f - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / t.getSize().y);

	std::vector<HitObject> objects;

	BeatMap map(829296);
	
	for (int i = 0; i < map.getHitObjectPositions().size(); i++)
	{
		objects.push_back(HitObject(map.getHitObjectPositions()[i], map.gethitObjectSpawnTimes()[i], 4.2f, 1.440f, playField));
		h.setPosition(playField.getPlayFieldStartPoint() + map.getHitObjectPositions()[i] * playField.getOsuPx());
		objects[i].hitCircle = h;
	}
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

		for (int i = 0; i < objects.size(); i++)
		{
			if (mapTime.getElapsedTime().asMilliseconds() >= objects[i].getSpawnTime() && !objects[i].getDrawingState())
			{
				objects[i].drawCircle(window);
				objects[i].approachTheCircle(deltaTime.asSeconds());
			}
			else if(objects[i].getDrawingState())
			{
				objects.erase(objects.begin() + i);
			}
			
		}
		
		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}
	return 0;
}