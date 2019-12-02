#include <SFML/Graphics.hpp>
#include<iostream>

sf::Time deltaTime;
sf::Clock runTime;
bool shouldLerp = false;
float timeStartedLerping;
float lerpTime=0.450;

void startLerp()
{
	timeStartedLerping = runTime.getElapsedTime().asSeconds();
	shouldLerp = true;
}

float Lerp(sf::Vector2f start, sf::Vector2f end, float timeStartedLerping, float lerpTime)
{
	float timeSinceStarted = runTime.getElapsedTime().asSeconds() - timeStartedLerping;
	float precentageComplete = timeSinceStarted / lerpTime;
	std::cout << precentageComplete << std::endl;
	float result = (start.x - end.x)*precentageComplete/0.225;
	if (precentageComplete > 1) shouldLerp = false;
	return result;
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

	sf::Clock deltaClock;

	sf::Vector2f startPos = approachCircle.getScale();
	sf::Vector2f endPos = hitCircle.getScale();

	startLerp();
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

		//if (timeStartedLerping ) shouldLerp = false;

		if (shouldLerp)
		{
			approachCircle.setScale(approachCircle.getScale().x - Lerp(startPos,endPos,timeStartedLerping,lerpTime) *deltaTime.asSeconds(), approachCircle.getScale().x - Lerp(startPos, endPos, timeStartedLerping, lerpTime) *deltaTime.asSeconds());
		}
		
		window.draw(approachCircle);
		window.draw(hitCircle);

		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}

	return 0;
}