// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_rect.h>

#include<oXu/core/scaling.hpp>

#include<oXu/beatmap/beatmapInfo.hpp>

#include<oXu/utils/vector2.hpp>

#include<oXu/components/textures.hpp>
#include<oXu/components/game/playField.hpp>
#include<oXu/components/game/models/hitCircldeModel.hpp>

namespace oxu
{

	class HitCircle
    {
    protected:
        SDL_Rect       ACRect;                   // approach circle SDL_Rect
        Vector2<float> ACInitialSize;            // the size the approach circle gets spawned with
        Vector2<float> ACFinalSize;              // position to which the approach circle lerps
        float          approachT = 0.0f;         // t value for lerp

        SDL_Rect       HCRect;                   // hit circle SDL_Rect

        Vector2<float> objTruePosition;          // the x, y values taken from the beatmap
        uint32_t       hitTime;                  // when the approach circle should be hit in milliseconds
        bool           doneApproaching = false;  // if the approach circle is done approaching or object has been hit

        SDL_Rect       comboRect;                // combo SDL_Rect
        int            combo;                    // actual combo integer

        float          ARInSeconds;

    public:
        HitCircle(const HitCircleModel &model, const PlayField &playField);

        const SDL_Rect *getHCRect();

        const SDL_Rect *getACRect();

        const SDL_Rect *getComboRect();

        const uint32_t &getHitTime();

        uint32_t       getSpawnTime();

        const int      &getCombo();

        void approachCircle(const double &dt);

        const bool &isHit();

        void hit();
    };
}
