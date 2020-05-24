#pragma once

#include<vector>
#include<math.h>


#include"hitCircle.hpp"
#include"../../utils/vector2.hpp"
#include"playField.hpp"

namespace oxu
{
	class Slider : public HitCircle
	{
	private:
		/* Slider control points including initial position */
		std::vector<Vector2<float>> controlPoints;
		
		/* The slider length from the beatmap file */
		double expectedLength;

		/* The slider type (Liner, Circle, Bezier) */
		uint8_t type;

		/* Length calculated after building the slider path */
		double calculatedLength = 0;

		/* Calculated path coords */
		std::vector<Vector2<float>> calculatedPath;

		void calculateLength();
		void calculatePath(PlayField &playField, const double &precision = 0.005);

	public:
		Slider(unsigned int infoArr[4], const std::vector<Vector2<float>> &controlPoints, const int &length,const uint8_t &sliderType, PlayField &playField);

		const std::vector<Vector2<float>> &getCalculatedPath();

		const std::vector<Vector2<float>> &getControlPoints();

		const double &getExpectedLength();
		const double &getCalculatedLength();

		const uint8_t &getSliderType();
	};
}