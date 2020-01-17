#pragma once

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
    bool sliding = false;

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

		this->hitCircle.setTexture(hitCircleTexture);

		//Set the origin to center of the circle, and recenter ==============
		this->hitCircle.setOrigin((sf::Vector2f)hitCircleTexture.getSize() / 2.0f);
		this->hitCircle.move((sf::Vector2f)hitCircleTexture.getSize() / 2.0f - this->hitCircle.getOrigin());
		//===================================================================
		this->spawnTime = spawnTime;

		this->hitCircle.setPosition(playField.getPlayFieldStartPoint().x + position.x*playField.getOsuPx(), playField.getPlayFieldStartPoint().y + position.y*playField.getOsuPx());

		//alternative (109-9*CS) * osuPX / hitCircleTexture.getSize().x
		this->hitCircle.setScale(((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().x, ((23.05f - (CS - 7.0f) * 4.4825f) * 2.0f * playField.getOsuPx()) / hitCircleTexture.getSize().y);

	}

    void moveOnStraightPath(const float &dt,const PlayField &playField, ApproachCircle &approachCircle)
	{
		if (approachCircle.getApproachState())
		{
            static sf::Clock cl;
            sf::Vector2f distance = {sliderPointsCoords[0] - initialPosition};

            //the problem is that the Clock remains in memory with the same value even for other objects
            //the clock needs to be reset when working with another object somehow

            if(cl.getElapsedTime().asSeconds() <= 0.100f)
            {
                sf::Vector2f AT = ((distance / 0.100f * playField.getOsuPx()) * dt);
                this->hitCircle.setPosition(this->hitCircle.getPosition() + AT);
            } 
                                                                               
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

    void drawBezierCurve(const std::vector<sf::Vector2f> &positions,const PlayField &playField,sf::RenderWindow &window)
    {
        sf::RectangleShape rect;
        rect.setSize({ 2,2 });
        for (float t = 0; t < 1; t += 0.001f)
        {
            sf::Vector2f gizm = { 0,0 };
            int power = positions.size() - 1;
            for (unsigned int i = 0; i < positions.size(); i++)
            {
                if (i == positions.size() - 1)
                {
                    gizm += positions[i] * static_cast<float>(std::pow(t, i));
                }
                else if (i > 0)
                {
                    gizm += static_cast<float>(std::pow(1 - t, power)) * positions[i] * (getPascalTriangleRow(positions)[i - 1] * static_cast<float>(std::pow(t, i)));

                }
                else
                    gizm += static_cast<float>(std::pow(1 - t, power)) * positions[i];
                power--;
            }
            power = positions.size() - 1;
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

void moveOnBezierCurve(const PlayField &playField, const float &dt, ApproachCircle &approachCircle)
	{
		static bool shouldCalculateCap = true;
		static std::vector<float> curvePoints;
		float sliderTime = 0.500f;

		if (shouldCalculateCap)
		{
			float arcLength = 0.0f;
			int it = 1;
			bool firstPoint = true;
			float tParam = 0;

			while (arcLength < sliderLength)
			{                
				arcLength += std::sqrt(std::pow((calculateBezierPoint(tParam) - calculateBezierPoint(tParam,0.0001f)).x,2) + std::pow((calculateBezierPoint(tParam) - calculateBezierPoint(tParam,0.0001f)).y, 2)) ;

				if (arcLength >= sliderLength / (sliderLength / 10) * it || firstPoint)
				{
					curvePoints.push_back(tParam);
					it++;
					firstPoint = false;
				}
				tParam += 0.0001f;
			}
			shouldCalculateCap = false;
		}

		static sf::Clock sliderElapsedTime;
		if (!approachCircle.getApproachState())
			sliderElapsedTime.restart();

		if (sliderElapsedTime.getElapsedTime().asSeconds() <= sliderTime && approachCircle.getApproachState())
		{
			static sf::Clock segmentTime;
			static uint8_t currentSegment = 1;

			if (segmentTime.getElapsedTime().asSeconds() <= sliderTime / (sliderLength / 10))
			{
				sf::Vector2f distanceBetweenPoints = calculateBezierPoint(curvePoints[currentSegment]) - calculateBezierPoint(curvePoints[currentSegment - 1]);
				sf::Vector2f AT = ((distanceBetweenPoints / (sliderTime / (sliderLength / 10)) * playField.getOsuPx()) * dt);
				this->hitCircle.setPosition(this->hitCircle.getPosition() + AT);
			}
			else if(currentSegment + 1 != curvePoints.size())
			{
				currentSegment++;
				segmentTime.restart();
			}
		}
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

    bool isSliding() const
    {
        return sliding;
    }
};