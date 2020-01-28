#pragma once

namespace oxu
{
	class Slider
	{
	private:
		sf::Sprite hitCircle;
		long spawnTime;
		std::vector<sf::Vector2f> sliderPointsCoords;
		sf::Vector2f initialPosition;
		int slides;
		float sliderLength;
		char sliderType;

		//for beziers and pc only=====
		std::vector<float> reparametarizedCurvePoints;
		bool shouldreparametarizeCurve = true;
		uint8_t currentSegment = 1;
		//============================

	public:

		Slider(
			const sf::Vector2f &position,
			const long &spawnTime,
			const float &CS,
			const std::vector<sf::Vector2f> &sliderPointsCoords,
			const int &slides,
			const float &sliderLength,
			const char &sliderType,
			const PlayField &playField,
			const sf::Texture &hitCircleTexture
		)
		{
			this->sliderPointsCoords = sliderPointsCoords;
			this->slides = slides;
			this->sliderLength = sliderLength;
			this->sliderType = sliderType;
			this->initialPosition = position;
			this->spawnTime = spawnTime;

			this->hitCircle.setTexture(hitCircleTexture);

			//Set the origin to center of the circle, and recenter ==============
			this->hitCircle.setOrigin((sf::Vector2f)hitCircleTexture.getSize() / 2.0f);
			this->hitCircle.move((sf::Vector2f)hitCircleTexture.getSize() / 2.0f - this->hitCircle.getOrigin());
			//===================================================================

			this->hitCircle.setPosition(playField.getPlayFieldStartPoint().x + position.x*playField.getOsuPx(), playField.getPlayFieldStartPoint().y + position.y*playField.getOsuPx());

			//alternative (109-9*CS) * osuPX / hitCircleTexture.getSize().x
			this->hitCircle.setScale(((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().x, ((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().y);

		}

		void moveFromAToB(sf::Vector2f &startPos, sf::Vector2f &endPos, const float &slideTime, const float &dt, const PlayField &playField)
		{
			if (currentSegment != reparametarizedCurvePoints.size())
			{
				sf::Vector2f distance = endPos - startPos;

				if (endPos.x > startPos.x)
				{
					if (((this->hitCircle.getPosition() - playField.getPlayFieldStartPoint()) / playField.getOsuPx()).x <= endPos.x && slides > 0)
					{
						sf::Vector2f AT = ((distance / slideTime * playField.getOsuPx()) * dt);
						this->hitCircle.setPosition(this->hitCircle.getPosition() + AT);
					}
					else
					{
						if (sliderType == 'L')
						{
							sf::Vector2f aux = endPos;
							endPos = startPos;
							startPos = aux;

							this->slides = this->slides - 1;
						}
						else if (sliderType == 'B' && currentSegment < reparametarizedCurvePoints.size())
						{
							++currentSegment;
						}
						else if (sliderType == 'B' && currentSegment == reparametarizedCurvePoints.size() - 1 && slides == 1)
						{
							--slides;
						}
					}
				}
				else if (endPos.x < startPos.x)
				{
					if (((this->hitCircle.getPosition() - playField.getPlayFieldStartPoint()) / playField.getOsuPx()).x >= endPos.x && slides > 0)
					{
						sf::Vector2f AT = ((distance / slideTime * playField.getOsuPx()) * dt);
						this->hitCircle.setPosition(this->hitCircle.getPosition() + AT);

					}
					else
					{
						if (sliderType == 'L')
						{
							sf::Vector2f aux = endPos;
							endPos = startPos;
							startPos = aux;

							this->slides = this->slides - 1;
						}
						else if (sliderType == 'B' && currentSegment < reparametarizedCurvePoints.size())
						{
							++currentSegment;
						}
						else if (sliderType == 'B' && currentSegment == reparametarizedCurvePoints.size() - 1 && slides == 1)
						{
							--slides;
						}
					}
				}
				else if (endPos.y < startPos.y)
				{
					if (((this->hitCircle.getPosition() - playField.getPlayFieldStartPoint()) / playField.getOsuPx()).y >= endPos.y && slides > 0)
					{
						sf::Vector2f AT = ((distance / slideTime * playField.getOsuPx()) * dt);
						this->hitCircle.setPosition(this->hitCircle.getPosition() + AT);

					}
					else
					{
						if (sliderType == 'L')
						{
							sf::Vector2f aux = endPos;
							endPos = startPos;
							startPos = aux;

							this->slides = this->slides - 1;
						}
						else if (sliderType == 'B' && currentSegment < reparametarizedCurvePoints.size())
						{
							++currentSegment;
						}
						else if (sliderType == 'B' && currentSegment == reparametarizedCurvePoints.size() - 1 && slides == 1)
						{
							--slides;
						}
					}

				}
				else if (endPos.y > startPos.y)
				{
					if (((this->hitCircle.getPosition() - playField.getPlayFieldStartPoint()) / playField.getOsuPx()).y <= endPos.y && slides > 0)
					{
						sf::Vector2f AT = ((distance / slideTime * playField.getOsuPx()) * dt);
						this->hitCircle.setPosition(this->hitCircle.getPosition() + AT);

					}
					else
					{
						if (sliderType == 'L')
						{
							sf::Vector2f aux = endPos;
							endPos = startPos;
							startPos = aux;

							this->slides = this->slides - 1;
						}
						else if (sliderType == 'B' && currentSegment < reparametarizedCurvePoints.size())
						{
							++currentSegment;
						}
						else if (sliderType == 'B' && currentSegment == reparametarizedCurvePoints.size() - 1 && slides == 1)
						{
							--slides;
						}
					}
				}
			}
		}

		void moveOnStraightSlider(const float &dt, const float &slideTime, const PlayField &playField, const ApproachCircle &approachCircle)
		{
			if (approachCircle.getApproachState())
			{
				moveFromAToB(initialPosition, sliderPointsCoords[0], slideTime, dt, playField);
			}
		}

		std::vector<int> getPascalTriangleRow(const std::vector<sf::Vector2f> &positions)
		{
			unsigned int n = 1;

			std::vector<int> row;
			row.push_back(1);
			row.push_back(1);

			std::vector<int> newRow;

			while (n < positions.size() - 1)
			{
				if (n + 1 != positions.size() - 1)
					newRow.push_back(1);
				for (unsigned int i = 0; i < row.size() - 1; i++)
				{
					newRow.push_back(row[i] + row[i + 1]);
				}
				if (n + 1 != positions.size() - 1)
					newRow.push_back(1);
				row = newRow;
				n++;
				newRow.clear();
			}

			return row;
		}

		void drawBezierCurve(const PlayField &playField, sf::RenderWindow &window)
		{
			sf::RectangleShape rect;
			rect.setSize({ 2,2 });
			for (float t = 0; t < 1; t += 0.001f)
			{
				sf::Vector2f gizm = { 0,0 };
				int power = sliderPointsCoords.size() - 1;
				for (unsigned int i = 0; i < sliderPointsCoords.size(); i++)
				{
					if (i == sliderPointsCoords.size() - 1)
					{
						gizm += sliderPointsCoords[i] * static_cast<float>(std::pow(t, i));
					}
					else if (i > 0)
					{
						gizm += static_cast<float>(std::pow(1 - t, power)) * sliderPointsCoords[i] * (getPascalTriangleRow(sliderPointsCoords)[i - 1] * static_cast<float>(std::pow(t, i)));

					}
					else
						gizm += static_cast<float>(std::pow(1 - t, power)) * sliderPointsCoords[i];
					power--;
				}
				power = sliderPointsCoords.size() - 1;
				gizm *= playField.getOsuPx();

				rect.setPosition(playField.getPlayFieldStartPoint() + gizm);
				window.draw(rect);
			}
		}

		sf::Vector2f calculateBezierPoint(const float &tParam, const float &offset = 0.0f)
		{
			sf::Vector2f bezierPoint;
			int power = sliderPointsCoords.size() - 1;
			for (unsigned int i = 0; i < sliderPointsCoords.size(); i++)
			{
				if (i == sliderPointsCoords.size() - 1)
					bezierPoint += sliderPointsCoords[i] * static_cast<float>(std::pow(tParam - offset, i));
				else if (i > 0)
					bezierPoint += static_cast<float>(std::pow(1 - (tParam - offset), power)) * sliderPointsCoords[i] * (getPascalTriangleRow(sliderPointsCoords)[i - 1] * static_cast<float>(std::pow(tParam - offset, i)));
				else
					bezierPoint += static_cast<float>(std::pow(1 - (tParam - offset), power)) * sliderPointsCoords[i];
				power--;
			}
			return bezierPoint;
		}

		void reparametarizeCurve()
		{
			float arcLength = 0.0f;
			int it = 1;
			bool firstPoint = true;
			float tParam = 0;

			while (arcLength < sliderLength)
			{
				arcLength += std::sqrt(std::pow((calculateBezierPoint(tParam) - calculateBezierPoint(tParam, 0.0001f)).x, 2) + std::pow((calculateBezierPoint(tParam) - calculateBezierPoint(tParam, 0.0001f)).y, 2));

				if (arcLength >= sliderLength / (sliderLength / 5) * it)
				{
					reparametarizedCurvePoints.push_back(tParam);
					it++;
					firstPoint = false;
				}
				tParam += 0.0001f;
			}
			shouldreparametarizeCurve = false;
		}

		void moveOnBezierSlider(const float &sliderTime, const PlayField &playField, const float &dt,const ApproachCircle &approachCircle,sf::RenderWindow &window)
		{
			if (shouldreparametarizeCurve)
				reparametarizeCurve();

			if (approachCircle.getApproachState())
			{
				if (slides > 0)
				{
					sf::Vector2f a = calculateBezierPoint(reparametarizedCurvePoints[currentSegment - 1]);
					sf::Vector2f b = calculateBezierPoint(reparametarizedCurvePoints[currentSegment]);

					moveFromAToB(a, b, sliderTime, dt, playField);
				}
			}

			//!!!the problem is i dont move on straight paths correctly!!!
		}

		sf::Vector2f getHitCircleScale() const
		{
			return this->hitCircle.getScale();
		}

		sf::Sprite getHitCircle() const
		{
			return this->hitCircle;
		}

		sf::Vector2f getPos() const
		{
			return this->hitCircle.getPosition();
		}

		long getSpawnTime() const
		{
			return this->spawnTime;
		}

		int getSlides() const
		{
			return slides;
		}

		char getSliderType() const
		{
			return sliderType;
		}
	};
}