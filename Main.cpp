#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>

sf::Clock runTime;

//Class that loads the textures
struct Textures
{
	Textures()
	{
		approachCircleTexture.setSmooth(true);
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
	}
	sf::Texture approachCircleTexture;
	sf::Texture hitCircleTexture;
};

class HitCircleSprites
{
public:
	HitCircleSprites()
	{

	}
private:
	//sf::Texture 
};

void setOriginAndReadjust(sf::Sprite &object, const sf::Vector2f &newOrigin)
{
	object.setOrigin(newOrigin);
	object.move(newOrigin - object.getOrigin());
	object.setPosition(400.0f, 400.0f);
}

class ApproachCirclesSprites : Textures
{
private:
	sf::Sprite approachCircle;
	float approachSpeed;
public:
	ApproachCirclesSprites(float approachSpeed,sf::Vector2f xy)
	{
		this->approachCircle.setTexture(approachCircleTexture);
		this->approachCircle.setScale(2.0f, 2.0f);
		//Set the origin to center of the circle, move the circle there======
		this->approachCircle.setOrigin(xy);
		this->approachCircle.move(xy - this->approachCircle.getOrigin());
		//===================================================================
		this->approachCircle.setPosition(400.0f, 400.0f);
		this->approachSpeed = approachSpeed;
	}

	float getAS()
	{
		return this->approachSpeed;
	}

	void approachTheCircle(sf::Vector2f AR)
	{
		this->approachCircle.setScale(this->approachCircle.getScale() - AR);
	}

	sf::Sprite getApproachCircle()
	{
		return this->approachCircle;
	}

};

void startLerp(bool &shouldLerp, float &timeStartedLerping)
{
	timeStartedLerping = runTime.getElapsedTime().asSeconds();
	shouldLerp = true;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "osu!", sf::Style::Fullscreen);
	Textures textures;
	//Sprites used====================================================================================
	ApproachCirclesSprites approachCircle(3.0, { 70,70 });

	sf::Sprite hitCircle;
	hitCircle.setTexture(textures.hitCircleTexture);

	//================================================================================================

	setOriginAndReadjust(hitCircle, { 64,64 });

	//Other utilities=================================================================================
	sf::Clock deltaClock;
	sf::Time deltaTime;
	bool shouldLerp = false;
	float timeStartedLerping;
	sf::Vector2f x = approachCircle.getApproachCircle().getScale();
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

		if (approachCircle.getApproachCircle().getScale().x<=1.0f){ }
		else
		{
			if (approachCircle.getApproachCircle().getScale().x <= hitCircle.getScale().x){ }
			else
				std::cout << runTime.getElapsedTime().asSeconds()-timeStartedLerping<<std::endl;
			approachCircle.approachTheCircle(((x - hitCircle.getScale())/approachCircle.getAS())*deltaTime.asSeconds());
		}
		
		window.draw(approachCircle.getApproachCircle());
		window.draw(hitCircle);

		window.display();
		deltaTime = deltaClock.restart();
		//===============================================================================
	}

	return 0;
}