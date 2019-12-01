#include <SFML/Graphics.hpp>
#include<iostream>

void setOriginAndReadjust(sf::Sprite &object, const sf::Vector2f &newOrigin)
{
	auto offset = newOrigin - object.getOrigin();
	object.setOrigin(newOrigin);
	object.move(offset);
	object.setPosition(400.0f, 400.0f);
}

void approachTheCircle(sf::Vector2f &hitCircleSize, sf::Sprite &approachCircle)
{
	if (approachCircle.getScale().x < hitCircleSize.x)
		approachCircle.setScale(2.0f, 2.0f);
	else
		approachCircle.setScale(approachCircle .getScale().x- 0.0003f, approachCircle.getScale().y - 0.0003f);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "osu!");

	//Textures used==================================================================================
	sf::Texture approachCircleTexture;
	approachCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/approachcircle.png");
	approachCircleTexture.setSmooth(true);

	sf::Texture number1Texture;
	number1Texture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/score-1.png");
	number1Texture.setSmooth(true);

	sf::Texture hitCircleTexture;
	hitCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/hitcircle.png");
	hitCircleTexture.setSmooth(true);
	//================================================================================================

	//Sprites used====================================================================================
	sf::Sprite approachCircle;
	approachCircle.setTexture(approachCircleTexture);
	approachCircle.setScale(2.0f,2.0f);

	sf::Sprite hitCircle;
	hitCircle.setTexture(hitCircleTexture);
	sf::Vector2f hitCircleSize = hitCircle.getScale();;

	sf::Sprite number1;
	number1.setTexture(number1Texture);
	number1.setPosition(hitCircle.getPosition().x + 387.0f, hitCircle.getPosition().y + 377.0f);
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

		setOriginAndReadjust(hitCircle, { 64,64 });
		setOriginAndReadjust(approachCircle, { 70,70 });
		approachTheCircle( hitCircleSize, approachCircle);

		window.draw(number1);
		window.draw(approachCircle);
		window.draw(hitCircle);

		window.display();
		//===============================================================================
	}

	return 0;
}