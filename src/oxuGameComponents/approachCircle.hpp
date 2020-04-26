// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_rect.h>

#include"../oxuUtils/vector2.hpp"

namespace oxu
{
	class ApproachCircle
	{
	private:
		SDL_Rect ac_rect;
		float halfTex_x;
    	float halfTex_y;
	public:
		ApproachCircle(const Vector2i &spawnPos, const Vector2i &texSize);

		const SDL_Rect *getSDLRect();

		void move(Vector2i pos);

	};
}
