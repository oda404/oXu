// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#pragma once

#include<SDL2/SDL_render.h>
#include<SDL2/SDL_image.h>

#include<thread>
#include<atomic>
#include<cstdint>

#include"../components/textures.hpp"
#include"../beatmap/mapManager.hpp"
#include"../beatmap/mapInfo.hpp"
#include"../utils/logger.hpp"

namespace oxu
{
    class GraphicsHandler 
    {
    private:
        MapManager        &mapManagerI    = MapManager::getInstance();
        MapInfo           &mapInfoI       = MapInfo::getInstance();
        Textures          &texturesI      = Textures::getInstance();

        SDL_Renderer      *w_renderer     = NULL;
        SDL_Window        *window         = NULL;
        SDL_GLContext     context;

        int               *maxFPS;

        std::atomic<bool> doneInit;
        bool              *w_isClosed;

    public:
        GraphicsHandler();
        ~GraphicsHandler();

        bool init(SDL_Window                   *window, 
                  std::shared_ptr<std::thread> *gThreadSource, 
                  bool                         *w_statePtr,
                  int                          *pMaxFPS);

        void render();
    };
}
