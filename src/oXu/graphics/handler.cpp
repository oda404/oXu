// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"handler.hpp"

#include<oXu/core/status.hpp>
#include<oXu/utils/logger.hpp>
#include<oXu/core/threading/threadsManager.hpp>
#include<oXu/graphics/renderer.hpp>

namespace oxu::GraphicsHandler
{
    static Thread *cp_thisThread;
    static SDL_Window *cp_window = NULL;
    static SongManager *cp_songManager;
    static SkinManager *cp_skinManager;

    static void updateThread()
    {
        Request l_request;

        while(true)
        {
            cp_thisThread->limitFPS();
            
            while(cp_thisThread->pipeline.pollRequest(l_request))
            {
                switch(l_request.instruction)
                {
                case Graphics::HALT_THREAD:
                    return;
                }
            }

            Renderer::clear();

            cp_songManager->getCurrentBeatmap()->renderObjects(*cp_skinManager->getCurrentSkin());

            Renderer::render();
        }
    }

    static bool initThread()
    {
        Renderer::init(cp_window);

        cp_skinManager->enumerateSkins();
		cp_skinManager->setCurrentSkin(0);
		cp_skinManager->getCurrentSkin()->setCursor();
		cp_skinManager->getCurrentSkin()->loadTextures();

        cp_thisThread->doneInit = true;

        updateThread();

        return true;
    }

    void init(SDL_Window *window_p, SongManager *songManager_p, SkinManager *skinManager_p)
    {
        cp_songManager = songManager_p;
        cp_skinManager = skinManager_p;
        cp_window = window_p;

        cp_thisThread = &ThreadsManager::get(Threads::GRAPHICS);
        cp_thisThread->setMaxFPS(240);
        cp_thisThread->start([]() -> bool { return initThread(); });
        cp_thisThread->doneInit = false;
        while(!cp_thisThread->doneInit);
    }
}
