#pragma once
#include<fstream>
#include<string>
#include<iostream>
#include<sstream>

class BeatMap
{
public:
	BeatMap(const int &mapId)
	{
		bool go = false;

		std::string line;
		std::ifstream file("E:/visualproj/SFMLosuBootleg/songs/829296 mafumafu - Inochi ni Kirawarete Iru/mafumafu - Inochi ni Kirawarete Iru. (KazuhikoRei) [Haruki's Easy].osu");
		while (std::getline(file,line))
		{
			if (line == "[HitObjects]")
			{
				go = true;
			}
			if (go && line != "[HitObjects]")
			{
				std::string sX ="", sY ="";
				int it = 0;
				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] != ',' && it == 0)
					{
						sX += line[i];
					}
					else if (line[i] != ',' && it < 2)
					{
						sY += line[i];
					}
					else if (line[i] == ',' && it >= 0 )
					{
						it++;
					}
				}
				int iX,iY;
				std::istringstream i1(sX);
				std::istringstream i2(sY);
				i1 >> iX;
				i2 >> iY;

				hitObjectPositions.push_back({ (float)iX , (float) iY });
			}
		}
		file.close();
	}

	std::vector<sf::Vector2f> getHitObjectPositions() const
	{
		return this->hitObjectPositions;
	}

private:
	std::vector<sf::Vector2f> hitObjectPositions;
};