#pragma once

struct Textures
{
	Textures()
	{
		this->approachCircleTexture.setSmooth(true);
		this->hitCircleTexture.setSmooth(true);
#ifdef _WIN32
		this->approachCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/approachcircle.png");
		this->hitCircleTexture.loadFromFile("E:/visualproj/SFMLosuBootleg/skins/hitcircle.png");
#else
#ifdef __linux__
		this->approachCircleTexture.loadFromFile("/root/Documents/SFMLosu!/SFMLosu/skins/approachcircle.png");
		this->hitCircleTexture.loadFromFile("/root/Documents/SFMLosu!/SFMLosu/skins/hitcircle.png");
#endif
#endif
	}

protected:
	sf::Texture approachCircleTexture;
	sf::Texture hitCircleTexture;
};