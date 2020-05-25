#pragma once

#include<vector>
#include<math.h>

#include<oXu/components/game/hitCircle.hpp>
#include<oXu/components/game/playField.hpp>
#include<oXu/components/game/sliderTypes.hpp>

#include<oXu/utils/pathCalculator.hpp>

#include<oXu/beatmap/beatmapInfo.hpp>

#include<oXu/utils/vector2.hpp>

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

		int repeats;

		/* Calculated path coords */
		std::vector<Vector2<float>> calculatedPath;

		void calculateLength();
		void calculatePath(const PlayField &playField);

	public:
		Slider(unsigned int infoArr[4], const std::vector<Vector2<float>> &controlPoints, const int &repeats, const double &length,const uint8_t &sliderType, const PlayField &playField, BeatmapInfo &mapInfo);

		const std::vector<Vector2<float>> &getCalculatedPath();

		const std::vector<Vector2<float>> &getControlPoints();

		const double &getExpectedLength();
		const double &getCalculatedLength();

		const uint8_t &getSliderType();
	};
}