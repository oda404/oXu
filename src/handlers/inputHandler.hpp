// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_events.h>

#include<vector>

#include"../utils/vector2.hpp"
#include"../beatmap/mapInfo.hpp"
#include"../handlers/soundHandler.hpp"

namespace oxu
{
    class InputHandler
    {
    private:
        SDL_Event event;

    public:
        InputHandler();
        
        void init(SoundHandler *pSoundHandler);

        void handleInput(bool &w_isClosed);
    };
}
