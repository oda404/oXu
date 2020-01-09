#pragma once
#include<fstream>
#include<string>
#include<sstream>

class BeatMap
{
public:
	BeatMap(const int &mapId)
	{
		bool go = false;

		std::string line;
		std::ifstream file("/root/Documents/osuBootleg/songs/829296 mafumafu - Inochi ni Kirawarete Iru/mafumafu - Inochi ni Kirawarete Iru. (KazuhikoRei) [Haruki's Easy].osu");
		while (std::getline(file,line))
		{
			line.erase(line.end()-1);
			if (line == "[HitObjects]")
			{
				go = true;
			}
			if (go && line != "[HitObjects]")
			{
				std::string sX = "", sY = "", time = "";
				int it = 0;
				for (int i = 0; i < line.size(); i++)
				{
					if (line[i] != ',' && it == 0)
					{
						sX += line[i];
					}
					else if (line[i] != ',' && it == 1)
					{
						sY += line[i];
					}
					else if (line[i] != ',' && it == 2)
					{
						time += line[i];
					}
					else if (line[i] == ',' && it >= 0 )
					{
						it++;
					}
				}
				int iX,iY,iTime;
				std::istringstream t(time);
				std::istringstream i1(sX);
				std::istringstream i2(sY);

				t >> iTime;
				i1 >> iX;
				i2 >> iY;
				
				hitObjectPositions.push_back({ (float)iX , (float) iY });
				hitObjectSpawnTimes.push_back(iTime);
			}
		}
		file.close();
	}

	std::vector<sf::Vector2f> getHitObjectPositions() const
	{
		return this->hitObjectPositions;
	}

	std::vector<int> gethitObjectSpawnTimes() const
	{
		return this->hitObjectSpawnTimes;
	}

private:
	std::vector<sf::Vector2f> hitObjectPositions;
	std::vector<int> hitObjectSpawnTimes;
};