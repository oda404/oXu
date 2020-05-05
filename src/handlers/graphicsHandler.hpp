// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_image.h>

#include<thread>
#include<atomic>

#include"../components/gameComponents.hpp"
#include"../components/textures.hpp"
#include"../beatmap/mapManager.hpp"

namespace oxu
{
    class GraphicsHandler 
    {
    private:
        GameComponents    &gcI            = GameComponents::getInstance();
        Textures          &texturesI      = Textures::getInstance();

        SDL_Renderer      *w_renderer     = NULL;
        SDL_Window        *window         = NULL;
        SDL_GLContext     context;

        uint32_t          lastTick        = 0;
	    double            deltaTime       = 0.0;
        int               maxFPS          = 60;

        std::atomic<bool> doneInit;
        std::atomic<bool> *w_isClosed;

    public:
        GraphicsHandler();
        ~GraphicsHandler();

        /* fuck that's one long line */
        bool init(SDL_Window *window, std::shared_ptr<std::thread> *gThreadSource, std::atomic<bool> *w_statePtr);

        void render();
    };
}