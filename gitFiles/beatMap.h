#pragma once
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>

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
#ifdef __linux__
			line.erase(line.end()-1);
#endif
			if (line == "[HitObjects]")
			{
				go = true;
			}
			if (go && line != "[HitObjects]")
			{
				std::string sX = "", sY = "", time = "", sCX="",sCY="";
				int it = 0;
				bool curveTypeCheck = true, curveYCoordsRead = false;

				for (unsigned int i = 0; i < line.size(); i++)
				{
					static bool curvePointsGo = false;
					static std::vector<sf::Vector2f> positions;

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
					else if (line[i] != ',' && it == 5)
					{
						if ((line[i] == 'P' || line[i] == 'B' || line[i] == 'L') && curveTypeCheck)
						{
							hitObjectsCurveType.push_back(line[i]);
							curvePointsGo = true;
							curveTypeCheck = false;
						}
						else if(curveTypeCheck)
						{
							hitObjectsCurveType.push_back('N');
							curveTypeCheck = false;
						}
						else if(curvePointsGo)
						{
							bool yDoneReading = false;
							float iCX, iCY;
							std::istringstream cX, cY;

							if (line[i] == ':')
							{
								cX = std::istringstream(sCX);
								cX >> iCX;

								//x

								curveYCoordsRead = true;
							}
							else if (line[i] == '|' && line[i - 1] != 'L' && line[i - 1] != 'P' && line[i - 1] != 'B')
							{
								sCY = "";
								sCX = "";
								curveYCoordsRead = false;
							}

							if (!curveYCoordsRead && line[i] != '|')
								sCX += line[i];
							else if(curveYCoordsRead && line[i] != ':')
								sCY += line[i];

							if (line[i + 1] == '|' || line[i + 1] == ',')
							{
								cY = std::istringstream(sCY);
								cY >> iCY;
								yDoneReading = true;
								//y
							}

							if (yDoneReading)
							{
								positions.push_back({ iCX, iCY });
								if (line[i + 1] == ',')
								{
									hitObjectsCurvePointsPositions.push_back(positions);
									positions.clear();
								}
							}
						}
					}
					else if (line[i] == ',')
					{
						curvePointsGo = false;
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
				
				hitObjectsPositions.push_back({ (float)iX , (float) iY });
				hitObjectsSpawnTimes.push_back(iTime);
			}
		}
		file.close();
	}

	//Getters=======================================================
	std::vector<sf::Vector2f> getHitObjectPositions() const
	{
		return this->hitObjectsPositions;
	}

	std::vector<int> gethitObjectSpawnTimes() const
	{
		return this->hitObjectsSpawnTimes;
	}

	std::vector<char> getHitObjectCurveType() const
	{
		return this->hitObjectsCurveType;
	}
	//=============================================================

private:
	std::vector<sf::Vector2f> hitObjectsPositions;
	std::vector<int> hitObjectsSpawnTimes;
	std::vector<std::vector<sf::Vector2f>> hitObjectsCurvePointsPositions;
	std::vector<char> hitObjectsCurveType;
};