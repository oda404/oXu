// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_rect.h>

#include"../../utils/vector2.hpp"
#include"../textures.hpp"
#include"../../beatmap/mapInfo.hpp"

#include"playField.hpp"

namespace oxu
{

	class HitCircle
    {
    private:
        /* Approach circle stuff */
        SDL_Rect       ACRect;
        Vector2<float> ACInitialSize;     // needed to scale the AC down
        Vector2<float> ACFinalSize;
        float          approachT = 0.0f;

        SDL_Rect       comboNumRect;
        int            combo;

        SDL_Rect       HCRect;
        Vector2<float> objTruePosition;   // needed to recenter after scaling
        uint32_t       spawnTime;         // in millis
        bool           isDone = false;

    public:
        HitCircle(unsigned int infoArr[4], const int &combo, PlayField &playField);

        SDL_Rect *getHCSDLRect();

        SDL_Rect *getACSDLRect();

        SDL_Rect *getComboNumRect();

        uint32_t &getSpawnTime();

        void approachCircle(const double &dt);

        const bool &isFinished();

        void finish();

        const int &getCombo();
    };
}
