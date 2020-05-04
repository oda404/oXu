// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>

#include"../handlers/graphicsHandler.hpp"
#include"../components/cursor.hpp"
#include"../beatmap/mapManager.hpp"

namespace oxu
{
    class Game
    {
    private:
        GraphicsHandler graphicsHandler;

        SDL_Window        *window     = NULL;
        std::atomic<bool> w_isClosed;
        
        std::shared_ptr<std::thread> graphicsThread;
        
    public:
        bool w_init();

        void w_clean();

        void g_loop();

    };
}