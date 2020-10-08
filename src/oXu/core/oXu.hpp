// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>

namespace oxu
{
    class oXu
    {
    private:
        SDL_Window *window = NULL;
        bool windowState = false;
        
    public:
        ~oXu();

        bool init();
        void update();
    };
}
