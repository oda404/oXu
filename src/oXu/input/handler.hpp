// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_events.h>

#include<oXu/utils/vector2.hpp>

namespace oxu
{
    class InputHandler
    {
    private:
        SDL_Event event;

    public:        
        void init();

        void handleInput(bool &w_isClosed);

        void handleEvents();
    };
}
