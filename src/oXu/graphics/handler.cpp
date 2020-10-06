// Copyright (c) Olaru Alexandru <olarualexandru404@gmail.com>
// Licensed under the MIT license found in the LICENSE file in the root of this repository.

#include"handler.hpp"

#include<oXu/core/status.hpp>
#include<oXu/utils/logger.hpp>
#include<oXu/core/threading/threadsManager.hpp>
#include<oXu/graphics/renderer.hpp>

namespace oxu
{
    static Thread *thisThread;

    void GraphicsHandler::init(SDL_Window *window_p, SongManager *songManager_p, SkinManager *skinManager_p)
    {
        mp_songManager = songManager_p;
        mp_skinManager = skinManager_p;
        mp_window = window_p;

        thisThread = &ThreadsManager::get(Threads::GRAPHICS);
        thisThread->setMaxFPS(240);
        thisThread->start([this]() -> bool { return initThread(); });
        thisThread->doneInit = false;
        while(!thisThread->doneInit);
    }

    bool GraphicsHandler::initThread()
    {
        Renderer::init(mp_window);

        mp_skinManager->enumerateSkins();
		mp_skinManager->setCurrentSkin(0);
		mp_skinManager->getCurrentSkin()->setCursor();
		mp_skinManager->getCurrentSkin()->loadTextures();

        thisThread->doneInit = true;

        updateThread();

        return true;
    }

    void GraphicsHandler::updateThread()
    {
        Request request;

        while(true)
        {
            thisThread->limitFPS();
            
            while(thisThread->pipeline.pollRequest(request))
            {
                switch(request.instruction)
                {
                case Graphics::HALT_THREAD:
                    return;
                }
            }

            Renderer::clear();

            mp_songManager->getCurrentBeatmap()->renderObjects(*mp_skinManager->getCurrentSkin());

            Renderer::render();
        }
    }
}
