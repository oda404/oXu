// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_rect.h>

namespace oxu
{
	class HitCircle
    {
    private:
        SDL_Rect circleRect;
        uint32_t spawnTime; // in millis

    public:
        HitCircle(unsigned int infoArr[5]);

        SDL_Rect *getSDLRect();
    };
}
