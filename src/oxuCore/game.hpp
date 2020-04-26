// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include"../oxuUtils/log.hpp"
#include"../oxuGameHandlers/graphicsHandler.hpp"

namespace oxu
{
    class Game
    {
    private:
        oxu::Log logUtil;

        oxu::GraphicsHandler graphicsHandler;

        SDL_Window *window = NULL;

        bool w_isClosed = false;
        double deltaTime = 0;
        uint64_t dt_now = 0, dt_last = 0;

    public:
        bool w_init();

        void w_clean();

        void g_loop();

        void g_calculateDeltaTime();
    };
}