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
        GraphicsHandler();

        /* Singleton instances */
        MapManager        &mapManagerI    = MapManager::getInstance();
        MapInfo           &mapInfoI       = MapInfo::getInstance();
        Textures          &texturesI      = Textures::getInstance();

        SDL_Renderer      *w_renderer     = NULL;
        SDL_Window        *window         = NULL;
        SDL_GLContext     context;

        unsigned int      *maxFPS;

        std::atomic<bool> doneInit;
        bool              *w_isClosed;

        /* render function */
        void render();

    public:
        ~GraphicsHandler();

        /* ================== Singleton stuff =================== */
        static GraphicsHandler &getInstance();

        GraphicsHandler(const GraphicsHandler&)            = delete;

        GraphicsHandler(GraphicsHandler&&)                 = delete;

        GraphicsHandler& operator=(const GraphicsHandler&) = delete;

        GraphicsHandler& operator=(GraphicsHandler&&)      = delete;
        /* ======================================================= */

        bool init(SDL_Window                   *window, 
                  std::shared_ptr<std::thread> *gThreadSource, 
                  bool                         *w_statePtr,
                  unsigned int                 *pMaxFPS);
    };
}
