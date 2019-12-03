#include <SFML/Graphics.hpp>
#include<iostream>

sf::Clock runTime;

void startLerp(bool &shouldLerp, float &timeStartedLerping)
{
	timeStartedLerping = runTime.getElapsedTime().asSeconds();
	shouldLerp = true;
}

void setOriginAndReadjust(sf::Sprite &object, const sf::Vector2f &newOrigin)
{
	object.setOrigin(newOrigin);
	object.move(newOrigin - object.getOrigin());
	object.setPosition(400.0f, 400.0f);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "osu!", sf::Style::Fullscreen);

	//Textures used==================================================================================
	sf::Texture approachCircleTexture;
	approachCircleTexture.setSmooth(true);

	sf::Texture number1Texture;
	number1Texture.setSmooth(true);

	sf::Texture hitCircleTexture;
	hitCircleTexture.setSmooth(true);

#ifdef _WIN32
	approachCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/approachcircle.png");
	hitCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/hitcircle.png");
#else
#ifdef __linux__
	approachCircleTexture.loadFromFile("/root/Documents/SFMLosu!/SFMLosu/skins/approachcircle.png");
	hitCircleTexture.loadFromFile("/root/Documents/SFMLosu!/SFMLosu/skins/hitcircle.png");
#endif
#endif

	//================================================================================================

	//Sprites used====================================================================================
	sf::Sprite approachCircle;
	approachCircle.setTexture(approachCircleTexture);
	approachCircle.setScale(2.0f, 2.0f);

	sf::Sprite hitCircle;
	hitCircle.setTexture(hitCircleTexture);

	//================================================================================================

	setOriginAndReadjust(hitCircle, { 64,64 });
	setOriginAndReadjust(approachCircle, { 70,70 });

	//Other utilities=================================================================================
	sf::Clock deltaClock;
	sf::Time deltaTime;
	bool shouldLerp = false;
	float timeStartedLerping;
	float x = approachCircle.getScale().x;
	float timer = 0.0f;
	//================================================================================================

	startLerp(shouldLerp,timeStartedLerping);
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

		if (approachCircle.getScale().x<=1.0f){ }
		else
		{
			if (approachCircle.getScale().x <= hitCircle.getScale().x){ }
			else
				std::cout << runTime.getElapsedTime().asSeconds()-timeStartedLerping<<std::endl;
			timer = 0.9f;
			approachCircle.setScale(approachCircle.getScale().x - ((x - hitCircle.getScale().x)/timer)*deltaTime.asSeconds(), approachCircle.getScale().x - ((x - hitCircle.getScale().x)/timer)*deltaTime.asSeconds());
		}
		
		window.draw(approachCircle);
		window.draw(hitCircle);

		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}

	return 0;
}