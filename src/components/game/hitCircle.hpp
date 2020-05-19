// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_rect.h>

#include"../../beatmap/mapInfo.hpp"

#include"../../utils/vector2.hpp"

#include"../textures.hpp"

#include"playField.hpp"

namespace oxu
{

	class HitCircle
    {
    private:
        SDL_Rect       ACRect;            // approach circle SDL_Rect
        Vector2<float> ACInitialSize;     // the size the approach circle gets spawned with
        Vector2<float> ACFinalSize;       // position to which the approach circle lerps
        float          approachT = 0.0f;  // t value for lerp

        SDL_Rect       comboRect;         // combo SDL_Rect
        int            combo;             // actual combo integer

        SDL_Rect       HCRect;            // hit circle SDL_Rect

        Vector2<float> objTruePosition;   // the x, y values taken from the beatmap
        uint32_t       hitTime;           // when the approach circle should be hit in milliseconds
        bool           done = false;      // if the approach circle is done approaching or object has been hit

    public:
        HitCircle(unsigned int infoArr[5], PlayField &playField);

        const SDL_Rect *getHCRect();

        const SDL_Rect *getACRect();

        const SDL_Rect *getComboRect();

        const uint32_t &getHitTime();

        void approachCircle(const double &dt);

        const bool &isDone();

        const int &getCombo();

        void hit();
    };
}
