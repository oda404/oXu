#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include"playField.h"
#include"beatMapParser.h"
#include"hitObjectLoader.h"

int main()
{
	sf::Vector2i screenSize = { 1920,1080 };
	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "oxu");
	window.setFramerateLimit(480);

	oxu::PlayField playField(screenSize);

	//cursor===========================================================
	sf::Image im;
	im.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/cursor.png");

	const sf::Uint8 *ptr = im.getPixelsPtr();

	sf::Cursor curs;
	curs.loadFromPixels(ptr, { 108,108 }, { 54,54 });
	window.setMouseCursor(curs);
	//cursor===========================================================
	//cursor trail=====================================================
	/*
	sf::Texture cursorTrailTexture;
	cursorTrailTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/cursortrail.png");

	sf::Sprite cursorTrailSprite;
	cursorTrailSprite.setTexture(cursorTrailTexture);

	sf::Mouse mouse;

	std::vector<sf::Vector2f> cursorPositions;
	//cursor trail=====================================================
	*/
	

	oxu::BeatMapParser map;

	oxu::HitObjectLoader aw;
	aw.createHitObjects(map, playField);
	
	
	sf::Music m;
	m.openFromFile("yomi.ogg");
	m.setVolume(0);

	//rect.setRotation(std::atan2(265.0f - 311.0f, 328.0f - 309.0f) * 180.0f / 3.1415f);

	sf::Clock deltaClock;
	sf::Time deltaTime;

	bool f = true;
	while (window.isOpen())
	{
		deltaTime = deltaClock.restart();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (f)
		{
			m.play();
			f = false;
		}
		//Render stuff to screen ====================================================

		window.display();
		window.clear();

		for (unsigned int i = 0; i < aw.hitCircleVector.size() - (aw.hitCircleVector.size() - 10); i++)
		{
			if (m.getPlayingOffset().asMilliseconds() >= aw.hitCircleVector[i].getSpawnTime() && !aw.approachCircleVector[i].getApproachState())
			{
				window.draw(aw.approachCircleVector[i].getApproachCircle());
				window.draw(aw.hitCircleVector[i].getHitCircle());
				aw.approachCircleVector[i].approachTheCircle(deltaTime.asSeconds(), aw.hitCircleVector[i].getHitCircleScale());

				if (i > 0)
					if (aw.approachCircleVector[i - 1].getApproachState())
					{
						aw.approachCircleVector.erase(aw.approachCircleVector.begin() + 0);
						aw.hitCircleVector.erase(aw.hitCircleVector.begin() + 0);
					}
			}
		}

		for (unsigned int i = 0; i < aw.sliderVector.size(); i++)
		{
			if (aw.sliderVector[i].getSliderType() == 'L')
			{
				if (m.getPlayingOffset().asMilliseconds() >= aw.sliderVector[i].getSpawnTime() && !aw.sliderApproachCircles[i].getApproachState())
				{
					window.draw(aw.sliderVector[i].getHitCircle());
					window.draw(aw.sliderApproachCircles[i].getApproachCircle());
					aw.sliderApproachCircles[i].approachTheCircle(deltaTime.asSeconds(), aw.sliderVector[i].getHitCircleScale());
				}
				else if (aw.sliderApproachCircles[i].getApproachState())
				{
					window.draw(aw.sliderVector[i].getHitCircle());
					aw.sliderVector[i].moveOnStraightSlider(deltaTime.asSeconds(), 0.300f, playField, aw.sliderApproachCircles[i]);

					if (aw.sliderVector[i].getSlides() == 0)
					{
						aw.sliderVector.erase(aw.sliderVector.begin() + i);
						aw.sliderApproachCircles.erase(aw.sliderApproachCircles.begin() + i);
					}
				}
			}
			else if (aw.sliderVector[i].getSliderType() == 'B')
			{
				if (m.getPlayingOffset().asMilliseconds() >= aw.sliderVector[i].getSpawnTime() && !aw.sliderApproachCircles[i].getApproachState())
				{
					window.draw(aw.sliderVector[i].getHitCircle());
					window.draw(aw.sliderApproachCircles[i].getApproachCircle());
					aw.sliderApproachCircles[i].approachTheCircle(deltaTime.asSeconds(), aw.sliderVector[i].getHitCircleScale());
				}
				else if (aw.sliderApproachCircles[i].getApproachState())
				{
					window.draw(aw.sliderVector[i].getHitCircle());
					aw.sliderVector[i].moveOnBezierSlider(0.1f,playField,deltaTime.asSeconds(),aw.sliderApproachCircles[i]);


				}
			}
		}

	}

	return 0;
}