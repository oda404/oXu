// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_events.h>

#include"../utils/vector2.hpp"

#include"../beatmap/mapManager.hpp"

namespace oxu
{
    class InputHandler
    {
    private:
        SDL_Event event;
        MapManager *beatmapManager;

    public:        
        void init(MapManager *mapManagerPtr);

        void handleInput(bool &w_isClosed);

        void handleEvents();
    };
}
