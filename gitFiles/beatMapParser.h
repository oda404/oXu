#pragma once
#include<fstream>
#include<string>
#include<sstream>
#include<array>
#include<iostream>

class BeatMapParser
{
public:
	BeatMapParser()
	{
		bool go = false;
		
		std::string line;
#ifdef _WIN32
		std::ifstream file("E:/visualproj/SFMLosuBootleg/songs/829296 mafumafu - Inochi ni Kirawarete Iru/mafumafu - Inochi ni Kirawarete Iru. (KazuhikoRei) [Haruki's Easy].osu");
#else
		std::ifstream file("/root/Documents/osuBootleg/songs/829296 mafumafu - Inochi ni Kirawarete Iru/mafumafu - Inochi ni Kirawarete Iru. (KazuhikoRei) [Haruki's Easy].osu");
#endif
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
				std::string sX = "", sY = "", time = "", sCX="",sCY="", sSlides="", sLength="";
				int it = 0;
				bool curveTypeCheck = true, curveYCoordsRead = false;
				bool isSlider = false;

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
							curveType.push_back(line[i]);
							curvePointsGo = true;
							curveTypeCheck = false;
							isSlider = true;
						}
						else if(curveTypeCheck)
						{
							//curveType.push_back('N');
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
									curvePointsCoords.push_back(positions);
									positions.clear();
								}
							}
						}
					}
					else if (line[i] != ',' && it == 6)
					{
						sSlides += line[i];
					}
					else if(line[i] != ',' && it == 7)
					{
						sLength += line[i];
					}
					else if (line[i] == ',')
					{
						curvePointsGo = false;
						it++;
					}
				}
				
				if (!isSlider)
				{
					int iX, iY, iTime;

					std::istringstream t(time);
					std::istringstream i1(sX);
					std::istringstream i2(sY);

					t >> iTime;
					i1 >> iX;
					i2 >> iY;

					hitCirclesPositions.push_back({ (float)iX , (float)iY });
					hitCirclesSpawnTimes.push_back(iTime);
				}
				else
				{
					int iX, iY, iTime, iSlides = 0, iLength = 0;

					std::istringstream t(time);
					std::istringstream i1(sX);
					std::istringstream i2(sY);
					std::istringstream isSlides(sSlides);
					std::istringstream isLength(sLength);

					t >> iTime;
					i1 >> iX;
					i2 >> iY;
					isSlides >> iSlides;
					isLength >> iLength;

					slidersPositions.push_back({ (float)iX , (float)iY });
					slidersSpawnTimes.push_back(iTime);
					nOfSlides.push_back(iSlides);
					sliderLengths.push_back(iLength);
				}
			}
		}
		file.close();
	}

	//Getters=======================================================
	std::vector<sf::Vector2f> getHitObjectPositions() const
	{
		return this->hitCirclesPositions;
	}

	std::vector<int> gethitObjectSpawnTimes() const
	{
		return this->hitCirclesSpawnTimes;
	}


	std::vector<int> getSlidersSpawnTimes()
	{
		return slidersSpawnTimes;
	}

	std::vector<sf::Vector2f> getSlidersPositions ()
	{
		return slidersPositions;
	}

	std::vector<char> getHitObjectCurveType() const
	{
		return this->curveType;
	}

	std::vector<std::vector<sf::Vector2f>> getSliderPointsCoord() const
	{
		return curvePointsCoords;
	}

	std::vector<int> getSlides() const
	{
		return nOfSlides;
	}

	std::vector<int> getSliderLength() const
	{
		return sliderLengths;
	}



	//=============================================================

private:
	//info about the map's hit circles===================================
	std::vector<sf::Vector2f> hitCirclesPositions;
	std::vector<int> hitCirclesSpawnTimes;
	//===================================================================
	//info about the map's sliders========================================
	std::vector<std::vector<sf::Vector2f>> curvePointsCoords;
	std::vector<sf::Vector2f> slidersPositions;
	std::vector<char> curveType;
	std::vector<int> slidersSpawnTimes;
	std::vector<int> nOfSlides;
	std::vector<int> sliderLengths;
	//===================================================================
};