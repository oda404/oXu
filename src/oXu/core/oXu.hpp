// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>

#include<oXu/graphics/handler.hpp>
#include<oXu/input/handler.hpp>

#include<oXu/beatmap/songManager.hpp>
#include<oXu/skin/skinManager.hpp>

namespace oxu
{
    class oXu
    {
    private:
        SDL_Window *window = NULL;
        bool windowState = false;

        GraphicsHandler graphicsHandler;
        InputHandler inputHandler;
        
    public:
        ~oXu();

        bool init();
        void update();
    };
}
