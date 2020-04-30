// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL.h>

#include"sceneManager.hpp"
#include"../beatmap/mapManager.hpp"

namespace oxu
{
    class Game
    {
    private:
        SceneManager    sceneManager;

        SDL_Window  *window     = NULL;
        bool        w_isClosed  = false;
        int         maxFPS      = 60;

    public:
        bool w_init();

        void w_clean();

        void g_loop();

    };
}