// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"handler.hpp"

#include<oXu/core/status.hpp>
#include<oXu/core/logger.hpp>
#include<oXu/graphics/renderer.hpp>
#include<oXu/core/threading/thread.hpp>

namespace oxu::GraphicsHandler
{
    static Thread c_selfThread;
    static SDL_Window *cp_window = NULL;
    static SongManager *cp_songManager;
    static SkinManager *cp_skinManager;

    static void updateThread()
    {
        Request l_request;

        while(true)
        {
            c_selfThread.limitFPS();
            
            while(c_selfThread.pipeline.pollRequest(l_request))
            {
                switch(l_request.instruction)
                {
                case Graphics::HALT_THREAD:
                    return;
                }
            }

            Renderer::clear();

            if(cp_songManager->getCurrentBeatmap() != nullptr)
            {
                cp_songManager->getCurrentBeatmap()->renderObjects(*cp_skinManager->getCurrentSkin());
            }

            Renderer::render();
        }
    }

    static void initThread()
    {
        Renderer::init(cp_window);

        cp_skinManager->enumerateSkins();
		cp_skinManager->setCurrentSkin(0);
        if(cp_skinManager->getCurrentSkin() != nullptr)
        {
            cp_skinManager->getCurrentSkin()->setCursor();
            cp_skinManager->getCurrentSkin()->loadTextures();
        }

        c_selfThread.doneInit = true;

        updateThread();
    }

    void init(SDL_Window *window_p, SongManager *songManager_p, SkinManager *skinManager_p)
    {
        cp_songManager = songManager_p;
        cp_skinManager = skinManager_p;
        cp_window = window_p;

        c_selfThread.setMaxFPS(240);
        /* paranoia */
        c_selfThread.doneInit = false;
        c_selfThread.start([] { initThread(); });
        while(!c_selfThread.doneInit);
    }

    void shutDown()
    {
        c_selfThread.pipeline.makeRequest(Graphics::HALT_THREAD);
        c_selfThread.join();
        Renderer::destroy();
    }
}
