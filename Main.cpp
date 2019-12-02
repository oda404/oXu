#include <SFML/Graphics.hpp>

void setOriginAndReadjust(sf::Sprite &object, const sf::Vector2f &newOrigin)
{
	object.setOrigin(newOrigin);
	object.move(newOrigin - object.getOrigin());
	object.setPosition(400.0f, 400.0f);
}

void approachTheCircle(const sf::Sprite &hitCircle, sf::Sprite &approachCircle)
{
	if (approachCircle.getScale().x < hitCircle.getScale().x)
		approachCircle.setScale(2.0f, 2.0f);
	else
		approachCircle.setScale(approachCircle .getScale().x- 0.0003f, approachCircle.getScale().y - 0.0003f);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "osu!");

	//Textures used==================================================================================
	sf::Texture approachCircleTexture;
	approachCircleTexture.setSmooth(true);

	sf::Texture number1Texture;
	number1Texture.setSmooth(true);

	sf::Texture hitCircleTexture;
	hitCircleTexture.setSmooth(true);

#ifdef _WIN32
	approachCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/approachcircle.png");
	number1Texture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/score-1.png");
	hitCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/hitcircle.png");
#else
#ifdef __linux__
	approachCircleTexture.loadFromFile("/root/Documents/'SFMLosu!'/SFMLosu/skins/approachcircle.png");
	number1Texture.loadFromFile("/ root / Documents / 'SFMLosu!' / SFMLosu / skins /score-1.png");
	hitCircleTexture.loadFromFile("/ root / Documents / 'SFMLosu!' / SFMLosu / skins /hitcircle.png");
#endif
#endif


	//================================================================================================

	//Sprites used====================================================================================
	sf::Sprite approachCircle;
	approachCircle.setTexture(approachCircleTexture);
	approachCircle.setScale(2.0f,2.0f);

	sf::Sprite hitCircle;
	hitCircle.setTexture(hitCircleTexture);

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
		approachTheCircle( hitCircle, approachCircle);

		window.draw(number1);
		window.draw(approachCircle);
		window.draw(hitCircle);

		window.display();
		//===============================================================================
	}

	return 0;
}