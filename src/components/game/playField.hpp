// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include"../../core/scaling.hpp"
#include"../../utils/vector2.hpp"

namespace oxu
{
	class PlayField
	{
	private:
		Vector2<float> playFieldStartPoint;
		
	public:
		PlayField();

		const Vector2<float> &getPlayFieldStartPoint();
		
	};
}
